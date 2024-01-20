#include "StateMachine.h"
#include <Arduino.h>

StateMachine::StateMachine(){
    currentStatePtr = nullptr;
    Serial.println("state machine constructor ");
}

void StateMachine::ChangeState(State& newState) {
    Serial.println("state change called");
    if (currentStatePtr != nullptr)
        currentStatePtr->ExitState(this);
    currentStatePtr = &newState;
    currentStatePtr->EnterState(this);
    Serial.println("state change done");
}

void StateMachine::Update() {
    Serial.println("update from state machine");
    currentStatePtr->Update(this);
}