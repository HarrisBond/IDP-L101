#include "Node.h"


Node::Node(WayPoint _waypoint){
    waypoint = _waypoint;
    nextIfSolid = nullptr;
    nextIfFoam = nullptr;
    nextIfEmpty = nullptr;
    nextTurnAngleIfSolid = 0;
    nextTurnAngleIfFoam = 0;
    nextTurnAngleIfEmpty = 0;
}

Node::Node(WayPoint _waypoint, Node* solid, Node* foam, Node* empty, int angleIfSolid, int angleIfFoam, int angleIfEmpty){
    waypoint = _waypoint;
    nextIfSolid = solid;
    nextIfFoam = foam;
    nextIfEmpty = empty;
    nextTurnAngleIfSolid = angleIfSolid;
    nextTurnAngleIfFoam = angleIfFoam;
    nextTurnAngleIfEmpty = angleIfEmpty;
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

void Node::SetNextAngleIfSolid(int newAngle){
    nextTurnAngleIfSolid = newAngle;
}

void Node::SetNextAngleIfFoam(int newAngle){
    nextTurnAngleIfFoam = newAngle;
}

void Node::SetNextAngleIfEmpty(int newAngle){
    nextTurnAngleIfEmpty = newAngle;
}

int Node::GetNextTurnAngle(BlockType type){
    switch (type){
        case BlockType::solid: return nextTurnAngleIfSolid; break;
        case BlockType::foam: return nextTurnAngleIfFoam; break;
        case BlockType::empty: return nextTurnAngleIfEmpty; break;
        default: return 0; break;
    }
}

WayPoint Node::GetWayPoint(){
    return waypoint;
}

Node* Node::GetNext(BlockType type){
    switch (type){
        case solid  :   return nextIfSolid;     break;
        case foam   :   return nextIfFoam;      break;
        case empty  :   return nextIfEmpty;     break;
        default     :   return nullptr;
    }
}