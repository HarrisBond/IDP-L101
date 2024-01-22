#pragma once
#include "LineFollowState.h"

class State;

class StateMachine {
    public:
        StateMachine();
        void ChangeState(State& newState);
        void Update();
    private:
        State* currentStatePtr;
};
