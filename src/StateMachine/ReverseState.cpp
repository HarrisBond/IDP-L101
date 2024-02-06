#include "ReverseState.h"
// #include "../Sequencer.h"
#include "StateMachine.h"
#include "BlindTurnState.h"
#include <Arduino.h>
// #include "../IO/IO.h";
#include "../Globals.h"
#include "../IO/IO.h"

ReverseState::ReverseState(){
}

void ReverseState::EnterState(StateMachine* parentMachine){
    Serial.println("Blind Forward State Entered");Serial.flush();
    motorController->SetRelativeSpeeds(-1.0, 0.0);
}

void ReverseState::Update(StateMachine* parentMachine){
    // Serial.println("    Update called on Block Drop State");Serial.flush();
    // forwardTimerMilliseconds -= time->GetDeltaTime();
    // if (forwardTimerMilliseconds <= 0.0){
    //     parentMachine->ChangeState(LineFollowState::GetInstance());
    // }

    bool outerLeft, outerRight, innerLeft, innerRight;
    IO::Sensors::LineSense(outerLeft, outerRight, innerLeft, innerRight);
    if (outerLeft || outerRight){
        parentMachine->ChangeState(BlindTurnState::GetInstance());
    }
}

void ReverseState::ExitState(StateMachine* parentMachine){

}

State& ReverseState::GetInstance(){
    static ReverseState singleton;
    return singleton;
}
