#pragma once
#include "Path.h"
#include "Node.h"
#include <Vector.h>

class Sequencer{
    public:
    Sequencer();
    static Path GetNextPath(BlockType type);
    private:
    static Node* currentNode;
    static Step* GetPath(WayPoint start, WayPoint end);
    static Step pathLUT[5][5][10];
    static void SetPathLUT(WayPoint start, WayPoint end, Step path[]);
};