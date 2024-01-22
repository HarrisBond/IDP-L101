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

    //all required paths are hard coded here and added to the lookup table
    //paths should only be added where the start waypoint is before the end in the waypoint enum
    //the corresponding reverse paths can then be generated and filled in algorithmically by 
    //iterating over the forward path backwards and reversing all turns.
    Step start_resA[] = {Step::forwardLeft, Step::forwardRight, Step::forwardRight};
    // pathLUT[WayPoint::start][WayPoint::resA].SetPath(start_resA);
    SetPathLUT(WayPoint::start, WayPoint::resA, start_resA);
} 

Path Sequencer::GetNextPath(BlockType type){
    WayPoint currentWayPoint = currentNode->GetWayPoint();
    Node* nextNode = currentNode->GetNext(type);
    WayPoint nextWayPoint = nextNode->GetWayPoint();

    //now need to get path from these start and end points
    Step* pathArray = GetPath(currentWayPoint, nextWayPoint);

    //delete the current node and set current to point to the next one
    delete currentNode;
    currentNode = nextNode;

    Path output = Path();
    output.SetPath(pathArray);
    return output;
}

Step* Sequencer::GetPath(WayPoint start, WayPoint end){
    return pathLUT[start][end];
}

void Sequencer::SetPathLUT(WayPoint start, WayPoint end, Step path[]){
    for (int i = 0; i < sizeof(path) / sizeof(path[0]); i++){
        pathLUT[start][end][i] = path[i];
    }
}