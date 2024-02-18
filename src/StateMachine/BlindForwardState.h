#pragma once

#include "State.h"
#include "../Sequencer.h"
#include "StateMachine.h"
#include <Arduino.h>
#include "../Globals.h"

//goes blindly forward for a time given by the sequencer (depending on where the bot is within the sequence)
//can also line follow for a short time if the program is at its end (the bot is returning to start).
//in future, this line follow code would be moved to a seperate file and referenced by this state and the line follow state
//to avoid code duplication.
class BlindForwardState : public State {
public:
    BlindForwardState();
    void EnterState(StateMachine* parentMachine);
    void Update(StateMachine* parentMachine);
    void ExitState(StateMachine* parentMachine);
    static State& GetInstance();
    void LineFollow();
private:
    float forwardTimerMilliseconds;
    const float defaultForwardTime = 500.0;
    const float startForwardTime = 1500.0;
    const float endForwardTime = 4200.0;
    const float endLineFollowTime = 2000.0;
    float lineFollowTime;

    bool lineFollowing;
};