#pragma once

#include "State.h"
#include "../Sequencer.h"
#include "StateMachine.h"
#include "BlindTurnState.h"
#include <Arduino.h>
#include "../Globals.h"
#include "../IO/IO.h"

//a variation of the blind reverse state which only requires one outer line sensor before starting the turn. This is less reliable but
//is the only way to detect junctions when approaching from a platform.
class ReversePlatformState : public State {
public:
    ReversePlatformState();
    void EnterState(StateMachine* parentMachine);
    void Update(StateMachine* parentMachine);
    void ExitState(StateMachine* parentMachine);
    static State& GetInstance();
private:

};