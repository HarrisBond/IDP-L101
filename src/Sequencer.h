#pragma once
#include "Paths/Path.h"
#include "Paths/Node.h"
#include "Globals.h"

#define MAX_PATH_LENGTH 10
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