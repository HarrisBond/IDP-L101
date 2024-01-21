#include "Sequencer.h"

Sequencer::Sequencer(){
    //initialize sequence tree
    //should go start, resA, green/red, resB, green/red, end
    Node startNode(WayPoint::start);

    Node resA(WayPoint::resA);
    currentNode->SetNextIfEmpty(&resA);

    Node redSolidA(WayPoint::redSolid);
    Node greenFoamA(WayPoint::greenFoam);
    resA.SetNextIfSolid(&redSolidA);
    resA.SetNextIfFoam(&greenFoamA);

    Node resB(WayPoint::resB);
    redSolidA.SetNextIfEmpty(&resB);
    greenFoamA.SetNextIfEmpty(&resB);

    Node redSolidB(WayPoint::redSolid);
    Node greenFoamB(WayPoint::greenFoam);
    resB.SetNextIfSolid(&redSolidB);
    resB.SetNextIfFoam(&greenFoamB);

    Node end(WayPoint::start);
    redSolidB.SetNextIfEmpty(&end);
    greenFoamB.SetNextIfEmpty(&end);
}

Path Sequencer::GetNextPath(BlockType type){
    WayPoint currentWayPoint = currentNode->GetWayPoint();
    Node* nextNode = currentNode->GetNext(type);
    WayPoint nextWayPoint = nextNode->GetWayPoint();
    //now need to get path from these start and end points

    //delete the current node and set current to point to the next one
    delete currentNode;
    currentNode = nextNode;
}