#pragma once
#include "LineFollowState.h"
#include <Arduino.h>

class State;

//stores the current state, updates it, and handles state changes.
class StateMachine {
    public:
        StateMachine();
        void ChangeState(State& newState);
        void Update();
    private:
        State* currentStatePtr;
};
