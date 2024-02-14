#include "FinishedState.h"


FinishedState::FinishedState(){
    
}

void FinishedState::EnterState(StateMachine* parentMachine){
    Serial.println("finished state entered");
    motorController->Stop();
    timeInState = 0.0;
}

void FinishedState::Update(StateMachine* parentMachine){
    timeInState += time->GetDeltaTime();
}

void FinishedState::ExitState(StateMachine* parentMachine){
}

State& FinishedState::GetInstance(){
    static FinishedState singleton;
    return singleton;
}
