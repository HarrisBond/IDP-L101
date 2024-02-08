#pragma once

#include "State.h"
#include "../Sequencer.h"
#include "StateMachine.h"
#include <Arduino.h>
#include "../Globals.h"

class FinishedState : public State {
public:
    FinishedState();
    void EnterState(StateMachine* parentMachine);
    void Update(StateMachine* parentMachine);
    void ExitState(StateMachine* parentMachine);
    static State& GetInstance();
private:
    float timeInState;
};