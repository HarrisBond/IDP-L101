#pragma once

#include "State.h"
#include "../Sequencer.h"
#include "StateMachine.h"
#include "BlindTurnState.h"
#include "ReversePlatformState.h"
#include <Arduino.h>


//executes a hardcoded sequence to drop a block onto a platform
class BlockDropState : public State {
public:
    BlockDropState();
    void EnterState(StateMachine* parentMachine);
    void Update(StateMachine* parentMachine);
    void ExitState(StateMachine* parentMachine);
    static State& GetInstance();
private:
    
};
