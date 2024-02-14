#include "ReversePlatformState.h"


ReversePlatformState::ReversePlatformState(){
}

void ReversePlatformState::EnterState(StateMachine* parentMachine){
    Serial.println("Reverse Platform State Entered");Serial.flush();
    motorController->SetRelativeSpeeds(-1.0, 0.0);
}

void ReversePlatformState::Update(StateMachine* parentMachine){
    bool outerLeft, outerRight, innerLeft, innerRight;
    IO::Sensors::LineSense(outerLeft, outerRight, innerLeft, innerRight);
    if (outerLeft || outerRight){
        parentMachine->ChangeState(BlindTurnState::GetInstance());
    }
}

void ReversePlatformState::ExitState(StateMachine* parentMachine){

}

State& ReversePlatformState::GetInstance(){
    static ReversePlatformState singleton;
    return singleton;
}
