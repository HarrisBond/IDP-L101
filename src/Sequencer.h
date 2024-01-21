#pragma once
#include "Path.h"
#include "Node.h"

class Sequencer{
    public:
    Sequencer();
    static Path GetNextPath(BlockType type);
    private:
    static Node* currentNode;
};