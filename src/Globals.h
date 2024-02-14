#pragma once
#include "Time/Time.h"
#include "IO/IO.h"
// #include "StateMachine/StateMachine.h"

//forward left/ right follows a line until a t junction, where it turns left/ right respectively
//forward block follows a line until a block, at which point it stops and picks it up
//forward platform follows a line until a platform, at which point it drops the held block
enum Step {forwardLeft, forwardRight, forwardBlock, forwardPlatform, returnStart, doIndustrialA, doIndustrialB, nullStep};
enum BlockType {solid, foam, empty};
enum WayPoint {start, resA, resB, industrialA, industrialB, redSolid, greenFoam};


extern Time* time;
extern IO::Motors* motorController;
#define BLOCK_DISTANCE_THRESHOLD 80