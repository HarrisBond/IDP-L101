#pragma once

#include "State.h"

class BlockDropState : public State {
public:
    BlockDropState();
    void EnterState(StateMachine* parentMachine);
    void Update(StateMachine* parentMachine);
    void ExitState(StateMachine* parentMachine);
    static State& GetInstance();
private:
    
};
