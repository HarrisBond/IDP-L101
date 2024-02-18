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

//does line following, detecting junctions and turning according to the current step in the path (stored by the line follow state).
//these paths are given by the sequencer class.
//Also checks various sensors depending on the current step (eg. checks the TOF sensor when approaching a block), and changes to 
//relevant states when these sensors reach set thresholds.
//this state is bloated and indicates the need for a restructuring of the code, probably to a heirarchical finite state machine.
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
    const float timeSinceJunctionThreshold = 1000.0;
    void LineFollow(Step currentStep);
    void HandleBothOuters(Step currentStep);
    void HandleBothInners(Step currentStep);
    void HandleLightFlash();
    float nextStepTimer;
    float lightTimer;
    float forwardBlockTimer;
    int sign(float x);
    DFRobot_VL53L0X TOFsensor;
};
