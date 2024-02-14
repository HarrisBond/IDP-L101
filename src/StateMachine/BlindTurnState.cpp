#include "BlindTurnState.h"


BlindTurnState::BlindTurnState(){
    turnTimerMilliseconds = 0.0;
}

void BlindTurnState::EnterState(StateMachine* parentMachine){
    Serial.println("Blind turn state entered");Serial.flush();
    int turnAngle = Sequencer::GetNextTurnAngle();
    if (turnAngle < 0){
        motorController->SetRelativeSpeeds(0.2, -1.0);
        turnAngle =- turnAngle;
    } else {
        //left
        motorController->SetRelativeSpeeds(0.2, 1.0);
    }
    turnTimerMilliseconds = turnAngle * 13;
}

void BlindTurnState::Update(StateMachine* parentMachine){
    turnTimerMilliseconds -= time->GetDeltaTime();
    if (turnTimerMilliseconds <= 0.0){
        motorController->Stop();
        parentMachine->ChangeState(BlindForwardState::GetInstance());
    }
}

void BlindTurnState::ExitState(StateMachine* parentMachine){

}

State& BlindTurnState::GetInstance(){
    static BlindTurnState singleton;
    return singleton;
}
