#pragma once

#include "State.h"
#include "../Sequencer.h"
#include "StateMachine.h"
#include "BlindTurnState.h"
#include <Arduino.h>
#include "../Globals.h"
#include "../IO/IO.h"


//reverses blindly until both outer line sensors have detected a line, at which point we have reached a junction and can transition
//into the blind turn state.
class ReverseState : public State {
public:
    ReverseState();
    void EnterState(StateMachine* parentMachine);
    void Update(StateMachine* parentMachine);
    void ExitState(StateMachine* parentMachine);
    static State& GetInstance();
private:
    bool leftDetected;
    bool rightDetected;
};