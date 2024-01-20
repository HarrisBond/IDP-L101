#include "StateMachine.h"
#include <Arduino.h>

LineFollowState::LineFollowState() : State() {
    Serial.println("line follow state constructor");
}

void LineFollowState::EnterState(StateMachine* parentMachine){
    //initialization
    Serial.println("Hello from the Line Follow State ");
}

void LineFollowState::Update(StateMachine* parentMachine) {
    Serial.println("Update fron the line follow state");
}

void LineFollowState::ExitState(StateMachine* parentMachine) {
    Serial.println("Exiting the line follow state");
}

State& LineFollowState::GetInstance() {
    static LineFollowState singleton;
    return singleton;
}