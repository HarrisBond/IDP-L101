#pragma once

enum BlockType {solid, foam, empty};
enum WayPoint {start, resA, resB, red, green};

class Node{
public:
    Node(WayPoint _waypoint, Node* solid, Node* foam, Node* empty);
    Node(WayPoint _waypoint);
    void SetNextIfSolid(Node* node);
    void SetNextIfFoam(Node* node);
    void SetNextIfEmpty(Node* node);
    Node* GetNext(BlockType type);
private:
    WayPoint waypoint;
    Node* nextIfSolid;
    Node* nextIfFoam;
    Node* nextIfEmpty;
};