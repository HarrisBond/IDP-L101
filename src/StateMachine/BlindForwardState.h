#pragma once

#include "State.h"
#include "../Sequencer.h"

class BlindForwardState : public State {
public:
    BlindForwardState();
    void EnterState(StateMachine* parentMachine);
    void Update(StateMachine* parentMachine);
    void ExitState(StateMachine* parentMachine);
    static State& GetInstance();
private:
    float forwardTimerMilliseconds;
    const float forwardTime = 500.0;
};