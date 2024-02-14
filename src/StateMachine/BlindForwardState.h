#pragma once

#include "State.h"
#include "../Sequencer.h"
#include "StateMachine.h"
#include <Arduino.h>
#include "../Globals.h"

class BlindForwardState : public State {
public:
    BlindForwardState();
    void EnterState(StateMachine* parentMachine);
    void Update(StateMachine* parentMachine);
    void ExitState(StateMachine* parentMachine);
    static State& GetInstance();
private:
    float forwardTimerMilliseconds;
    const float defaultForwardTime = 500.0;
    const float startForwardTime = 1500.0;
    const float endForwardTime = 2000.0;
};