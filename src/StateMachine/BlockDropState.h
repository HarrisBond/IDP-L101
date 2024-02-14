#pragma once

#include "State.h"
#include "../Sequencer.h"
#include "StateMachine.h"
#include "BlindTurnState.h"
#include "ReversePlatformState.h"
#include <Arduino.h>

class BlockDropState : public State {
public:
    BlockDropState();
    void EnterState(StateMachine* parentMachine);
    void Update(StateMachine* parentMachine);
    void ExitState(StateMachine* parentMachine);
    static State& GetInstance();
private:
    
};
