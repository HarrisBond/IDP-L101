#include "BlindForwardState.h"


BlindForwardState::BlindForwardState(){
    forwardTimerMilliseconds = 0.0;
}

void BlindForwardState::EnterState(StateMachine* parentMachine){
    if (!Sequencer::HasStarted()){
        forwardTimerMilliseconds = startForwardTime;
    } else if (Sequencer::IsFinishing()){
        forwardTimerMilliseconds = endForwardTime;
    } else {
        forwardTimerMilliseconds = defaultForwardTime;
    }
    Serial.println("Blind Forward State Entered");Serial.flush();
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
