#pragma once
#include "../Globals.h"


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
    int nextTurnAngleIfSolid;
    int nextTurnAngleIfFoam;
    int nextTurnAngleIfEmpty;
};