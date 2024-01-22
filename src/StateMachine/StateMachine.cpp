#include "StateMachine.h"
#include <Arduino.h>

StateMachine::StateMachine(){
    currentStatePtr = nullptr;
    Serial.println("state machine constructor");
    Serial.flush();
}

void StateMachine::ChangeState(State& newState) {
    Serial.println("state change called");
    Serial.flush();
    if (currentStatePtr != nullptr)
        currentStatePtr->ExitState(this);
    currentStatePtr = &newState;
    currentStatePtr->EnterState(this);
    Serial.println("state change done");
    Serial.flush();
}

void StateMachine::Update() {
    Serial.println("update from state machine");
    Serial.flush();
    currentStatePtr->Update(this);
}