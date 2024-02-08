#pragma once
#include "Time/Time.h"
#include "IO/IO.h"
// #include "StateMachine/StateMachine.h"

//forward left/ right follows a line until a t junction, where it turns left/ right respectively
//forward block follows a line until a block, at which point it stops and picks it up
//forward platform follows a line until a platform, at which point it drops the held block
enum Step {forwardLeft, forwardRight, forwardBlock, forwardPlatform, returnStart, nullStep};
enum BlockType {solid, foam, empty};
enum WayPoint {start, resA, resB, redSolid, greenFoam};

#define OUTER_LEFT_LINE_SENSOR_PIN 5
#define OUTER_RIGHT_LINE_SENSOR_PIN 2
#define INNER_LEFT_LINE_SENSOR_PIN 4
#define INNER_RIGHT_LINE_SENSOR_PIN 3

extern Time* time;
extern IO::Motors* motorController;
#define BLOCK_DISTANCE_THRESHOLD 0.1

