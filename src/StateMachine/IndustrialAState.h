#pragma once

#include "State.h"
#include "BlockPickupState.h"
#include "../Sequencer.h"
#include "StateMachine.h"
#include <Arduino.h>
#include "../Globals.h"

class IndustrialAState : public State {
public:
    IndustrialAState();
    void EnterState(StateMachine* parentMachine);
    void Update(StateMachine* parentMachine);
    void ExitState(StateMachine* parentMachine);
    static State& GetInstance();
    void UpdateFirstForward();
    void UpdateSecondForward(StateMachine* parentMachine);
    void LineFollow();
private:
    enum industrialState{firstForward, secondForward};
    industrialState state;
    float timer;
    const float firstForwardTime = 1000;
    const float secondForwardTime = 1000;
};