#pragma once

#include "State.h"
#include "../Sequencer.h"
#include "StateMachine.h"
#include "BlindTurnState.h"
#include <Arduino.h>
#include "../Globals.h"
#include "../IO/IO.h"

class ReversePlatformState : public State {
public:
    ReversePlatformState();
    void EnterState(StateMachine* parentMachine);
    void Update(StateMachine* parentMachine);
    void ExitState(StateMachine* parentMachine);
    static State& GetInstance();
private:

};