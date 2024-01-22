#pragma once
#include "Paths/Path.h"
#include "Paths/Node.h"
#include <Vector.h>

#define MAX_PATH_LENGTH 10
class Sequencer{
    public:
        Sequencer() = delete;
        static void Initialize();
        static void GetNextPath(BlockType type, Path* path);
    private:
        static Node* currentNode;
        static Step* GetPath(WayPoint start, WayPoint end);
        static Step pathLUT[5][5][MAX_PATH_LENGTH];
        static void SetPathLUT(WayPoint start, WayPoint end, Step path[], int pathLength);
};