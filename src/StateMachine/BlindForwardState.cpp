#include "BlindForwardState.h"


BlindForwardState::BlindForwardState(){
    forwardTimerMilliseconds = 0.0;
}

void BlindForwardState::EnterState(StateMachine* parentMachine){
    Serial.println("Blind Forward State Entered");Serial.flush();
    if (!Sequencer::HasStarted()){
        forwardTimerMilliseconds = startForwardTime;
    } else if (Sequencer::IsFinishing()){
        forwardTimerMilliseconds = endForwardTime;
    } else {
        forwardTimerMilliseconds = defaultForwardTime;
    }
    motorController->SetRelativeSpeeds(1.0, 0.0);
}

void BlindForwardState::Update(StateMachine* parentMachine){
    forwardTimerMilliseconds -= time->GetDeltaTime();
    if (forwardTimerMilliseconds <= 0.0){
        motorController->Stop();
        parentMachine->ChangeState(LineFollowState::GetInstance());
    }
}

void BlindForwardState::ExitState(StateMachine* parentMachine){

}

State& BlindForwardState::GetInstance(){
    static BlindForwardState singleton;
    return singleton;
}
