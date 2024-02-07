#include "FinishedState.h"
// #include "../Sequencer.h"
#include "StateMachine.h"
#include <Arduino.h>
// #include "../IO/IO.h";
#include "../Globals.h"

FinishedState::FinishedState(){
    
}

void FinishedState::EnterState(StateMachine* parentMachine){
    motorController->Stop();
    timeInState = 0.0;
}

void FinishedState::Update(StateMachine* parentMachine){
    // Serial.println("    Update called on Block Drop State");Serial.flush();
    timeInState += time->GetDeltaTime();
    // 
}

void FinishedState::ExitState(StateMachine* parentMachine){

}

State& FinishedState::GetInstance(){
    static FinishedState singleton;
    return singleton;
}
