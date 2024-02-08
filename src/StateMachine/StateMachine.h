#pragma once
#include "LineFollowState.h"
#include <Arduino.h>

class State;

class StateMachine {
    public:
        StateMachine();
        void ChangeState(State& newState);
        void Update();
    private:
        State* currentStatePtr;
};
