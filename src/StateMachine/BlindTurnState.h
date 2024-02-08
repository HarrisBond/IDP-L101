#pragma once

#include "State.h"
#include "../Sequencer.h"
#include "StateMachine.h"
#include "BlindForwardState.h"
#include <Arduino.h>
#include "../Globals.h"

class BlindTurnState : public State {
public:
    BlindTurnState();
    void EnterState(StateMachine* parentMachine);
    void Update(StateMachine* parentMachine);
    void ExitState(StateMachine* parentMachine);
    static State& GetInstance();
private:
    float turnTimerMilliseconds;
};
