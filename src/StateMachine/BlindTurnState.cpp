#include "BlindTurnState.h"
// #include "../Sequencer.h"
#include "StateMachine.h"
#include "BlindForwardState.h"
#include <Arduino.h>
// #include "../IO/IO.h";
#include "../Globals.h"

BlindTurnState::BlindTurnState(){
    turnTimerMilliseconds = 0.0;
}

void BlindTurnState::EnterState(StateMachine* parentMachine){
    Serial.println("Turn 180 state entered");Serial.flush();
    // turnTimer = maxTurnTime;
    int turnAngle = Sequencer::GetNextTurnAngle();
    if (turnAngle < 0){
        motorController->Right();
        turnAngle =- turnAngle;
    } else {
        motorController->Left();
    }
    turnTimerMilliseconds = turnAngle * 17;
    // motorController->Left();
    motorController->SetRelativeSpeeds(-0.2, 1.0);
}

void BlindTurnState::Update(StateMachine* parentMachine){
    // Serial.println("    Update called on Block Drop State");Serial.flush();
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
