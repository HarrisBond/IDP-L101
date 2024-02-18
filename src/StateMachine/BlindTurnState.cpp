#include "BlindTurnState.h"


BlindTurnState::BlindTurnState(){
    turnTimerMilliseconds = 0.0;
}

void BlindTurnState::EnterState(StateMachine* parentMachine){
    Serial.println("Blind turn state entered");Serial.flush();
    int turnAngle = Sequencer::GetNextTurnAngle();
    if (turnAngle < 0){
        //right
        motorController->SetRelativeSpeeds(0.2, -1.0);
        turnAngle =- turnAngle;
    } else {
        //left
        motorController->SetRelativeSpeeds(0.2, 1.0);
    }
    //13 is a rough conversion factor which gets the time in milliseconds required to turn turnAngle in degrees
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
