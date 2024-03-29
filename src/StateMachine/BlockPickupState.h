#pragma once

#include "State.h"
#include "../IO/IO.h"

class BlockPickupState : public State {
public:
    BlockPickupState();
    void EnterState(StateMachine* parentMachine);
    void Update(StateMachine* parentMachine);
    void ExitState(StateMachine* parentMachine);
    static State& GetInstance();
private:
    float forwardTimerMilliseconds;
    void LineFollow();
};
