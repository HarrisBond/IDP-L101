#pragma once

#include "State.h"
#include "../Sequencer.h"
#include "StateMachine.h"
#include "BlindForwardState.h"
#include <Arduino.h>
#include "../Globals.h"


//turns blindly (ignoring line sensors) for a time set by the sequencer object
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
