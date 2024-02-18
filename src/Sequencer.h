#pragma once
#include "Paths/Path.h"
#include "Paths/Node.h"
#include "Globals.h"
#include <Arduino.h>
#include "stdlib.h"

#define MAX_PATH_LENGTH 10

//responsible for coordinating the high level function of the robot eg path planning. States within the state machine ask
//sequencer for instructions which depend on the state of the robot within the course.
class Sequencer{
    public:
        Sequencer() = delete;
        static void Initialize();
        static void GetNextPath(Path* path);
        static void SetBlockType(BlockType newType);
        static void SetNextTurnAngle(int newTurnAngle);
        static int GetNextTurnAngle();
        static bool HasStarted();
        static bool IsFinishing();
    private:
        static Node* currentNode;
        static Step* GetPath(WayPoint start, WayPoint end);
        static Step* pathLUT[5][5];
        static void SetUpPathLUT();
        static void SetPathLUT(WayPoint start, WayPoint end, Step* path);
        static BlockType currentBlockType;
        static int nextTurnAngle;
        static bool started;
        static bool finishing;
};