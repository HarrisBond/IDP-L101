#include "ReverseState.h"


ReverseState::ReverseState(){
}

void ReverseState::EnterState(StateMachine* parentMachine){
    Serial.println("Blind Forward State Entered");Serial.flush();
    motorController->SetRelativeSpeeds(-1.0, 0.0);
    leftDetected = false;
    rightDetected = false;
}

void ReverseState::Update(StateMachine* parentMachine){
    bool outerLeft, outerRight, innerLeft, innerRight;
    IO::Sensors::LineSense(outerLeft, outerRight, innerLeft, innerRight);
    // if (outerLeft || outerRight){
    //     parentMachine->ChangeState(BlindTurnState::GetInstance());
    // }
    if (outerRight)rightDetected = true;
    if (outerLeft)leftDetected = true;
    if (rightDetected && leftDetected){
        parentMachine->ChangeState(BlindTurnState::GetInstance());
        return;
    }
}

void ReverseState::ExitState(StateMachine* parentMachine){

}

State& ReverseState::GetInstance(){
    static ReverseState singleton;
    return singleton;
}
