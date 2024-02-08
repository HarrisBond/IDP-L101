#include "StateMachine.h"


StateMachine::StateMachine(){
    currentStatePtr = nullptr;
}

void StateMachine::ChangeState(State& newState) {
    Serial.println("state change called");
    Serial.flush();
    if (currentStatePtr != nullptr)
        currentStatePtr->ExitState(this);
    currentStatePtr = &newState;
    currentStatePtr->EnterState(this);
}

void StateMachine::Update() {
    currentStatePtr->Update(this);
}