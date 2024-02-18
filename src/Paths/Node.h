#pragma once
#include "../Globals.h"

//used by sequencer to store the decision tree which is traversed throughout the program
class Node{
public:
    Node(WayPoint _waypoint, Node* solid, Node* foam, Node* empty, int angleIfSolid, int angleIfFoam, int angleIfEmpty);
    Node(WayPoint _waypoint);
    void SetNextIfSolid(Node* node);
    void SetNextIfFoam(Node* node);
    void SetNextIfEmpty(Node* node);
    void SetNextAngleIfSolid(int newAngle);
    void SetNextAngleIfFoam(int newAngle);
    void SetNextAngleIfEmpty(int newAngle);
    WayPoint GetWayPoint();
    Node* GetNext(BlockType type);
    int GetNextTurnAngle(BlockType type);
private:
    WayPoint waypoint;
    Node* nextIfSolid;
    Node* nextIfFoam;
    Node* nextIfEmpty;
    //these turn angles are the angle to blindly turn after the current waypoint, depending on the current block type
    int nextTurnAngleIfSolid;
    int nextTurnAngleIfFoam;
    int nextTurnAngleIfEmpty;
};