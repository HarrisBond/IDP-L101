#pragma once

#include "State.h"
#include "../Sequencer.h"
#include "StateMachine.h"
#include <Arduino.h>
#include "../Globals.h"

//currently does nothing but provide a controlled way to end the program. Could include indicator lights in future to
//announce to a user that the program is done.
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