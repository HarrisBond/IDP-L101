#include "Node.h"

Node::Node(WayPoint _waypoint){
    waypoint = _waypoint;
    nextIfSolid = nullptr;
    nextIfFoam = nullptr;
    nextIfEmpty = nullptr;
}

Node::Node(WayPoint _waypoint, Node* solid, Node* foam, Node* empty){
    waypoint = _waypoint;
    nextIfSolid = solid;
    nextIfFoam = foam;
    nextIfEmpty = empty;
}

void Node::SetNextIfSolid(Node* node){
    nextIfSolid = node;
}

void Node::SetNextIfFoam(Node* node){
    nextIfFoam = node;
}

void Node::SetNextIfEmpty(Node* node){
    nextIfEmpty = node;
}

Node* Node::GetNext(BlockType type){
    switch (type){
        case solid  :   return nextIfSolid;     break;
        case foam   :   return nextIfFoam;      break;
        case empty  :   return nextIfEmpty;     break;
        default     :   return nullptr;
    }
}