#include "ReverseState.h"


ReverseState::ReverseState(){
}

void ReverseState::EnterState(StateMachine* parentMachine){
    Serial.println("Blind Forward State Entered");Serial.flush();
    motorController->SetRelativeSpeeds(-1.0, 0.0);
}

void ReverseState::Update(StateMachine* parentMachine){
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
