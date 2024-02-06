#pragma once

#include "State.h"
#include "../Sequencer.h"

class BlindTurnState : public State {
public:
    BlindTurnState();
    void EnterState(StateMachine* parentMachine);
    void Update(StateMachine* parentMachine);
    void ExitState(StateMachine* parentMachine);
    static State& GetInstance();
private:
    float turnTimerMilliseconds;
    // const float maxTurnTime = 2500.0;
};
