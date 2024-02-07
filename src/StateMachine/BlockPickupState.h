#pragma once

#include "State.h"
#include "../IO/IO.h"
#include "../Globals.h"
#include <Servo.h>

#define LIFT_ANGLE 10

class BlockPickupState : public State {
public:
    BlockPickupState();
    void EnterState(StateMachine* parentMachine);
    void Update(StateMachine* parentMachine);
    void ExitState(StateMachine* parentMachine);
    static State& GetInstance();
private:
    unsigned long currentTime;
    bool touching;
    bool touched;
    int touchingCount;
    
    Servo lifter;
    BlockType currentBlockType;
    float UltraRead(float dist_t, BlockType &currentBlockType);
    void TouchStateDetect(float *dist_t, BlockType &currentBlockType);
    void BlockPick();
    void PickingLED();
};
