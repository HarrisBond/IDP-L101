#pragma once
#include "State.h"
#include "../Paths/Path.h"
#include "StateMachine.h"
#include "BlockPickupState.h"
#include "BlockDropState.h"
#include "BlindForwardState.h"
#include "FinishedState.h"
#include <Arduino.h>
#include "../IO/IO.h"
#include "../Time/Time.h"
#include "../Sequencer.h"
#include "../Globals.h"


class LineFollowState : public State {
public:
    LineFollowState();
    void EnterState(StateMachine* parentMachine);
    void Update(StateMachine* parentMachine);
    void ExitState(StateMachine* parentMachine);
    static State& GetInstance();
private:
    Path currentPath;
    float timeSinceJunction;
    const float timeSinceJunctionThreshold = 1500.0;
    void LineFollow(Step currentStep);
    void OtherLineFollow();
    void OtherLineFollowReverse();
    void HandleBothOuters(Step currentStep);
    void HandleBothInners(Step currentStep);
    void HandleLightFlash();
    float nextStepTimer;
    float lightTimer;
    float forwardBlockTimer;
    int sign(float x);
    DFRobot_VL53L0X TOFsensor;
};
