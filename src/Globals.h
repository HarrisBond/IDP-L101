#pragma once
#include "Time/Time.h"
#include "IO/IO.h"
// #include "StateMachine/StateMachine.h"

//forwardLeft/ forwardRight follows a line until a t junction, where it turns left/ right respectively
//forward block follows a line until a block, at which point it stops and picks it up
//forward platform follows a line until a platform, at which point it drops the held block
//return start goes forward for a set time before entering the finished state
enum Step {forwardLeft, forwardRight, forwardBlock, forwardPlatform, returnStart, nullStep};
enum BlockType {solid, foam, empty};
enum WayPoint {start, resA, resB, redSolid, greenFoam};


extern Time* time;
extern IO::Motors* motorController;
#define BLOCK_DISTANCE_THRESHOLD 120