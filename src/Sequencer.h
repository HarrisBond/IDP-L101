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
    static Path GetPath(WayPoint start, WayPoint end);
    static Path pathLUT[5][5];
};