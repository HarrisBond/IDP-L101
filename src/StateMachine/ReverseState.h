#pragma once

#include "State.h"
#include "../Sequencer.h"

class ReverseState : public State {
public:
    ReverseState();
    void EnterState(StateMachine* parentMachine);
    void Update(StateMachine* parentMachine);
    void ExitState(StateMachine* parentMachine);
    static State& GetInstance();
private:
};