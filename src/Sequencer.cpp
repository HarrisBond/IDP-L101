#include "Sequencer.h"
#include <Arduino.h>

Node* Sequencer::currentNode = nullptr;
Step Sequencer::pathLUT[5][5][MAX_PATH_LENGTH];

void Sequencer::Initialize(){
    // for (unsigned int i = 0; i < sizeof(pathLUT) / sizeof(pathLUT[0]); i++){
    //     for (unsigned int j = 0; j < sizeof(pathLUT[0]) / sizeof(pathLUT[0][0]); j++){
    //         for (unsigned int k = 0; k < sizeof(pathLUT[0][0]) / sizeof(pathLUT[0][0][0]); k++){
    //             pathLUT[i][j][k] = Step::null;
    //         }
    //     }
    // }
    // return;
    //initialize sequence tree
    //should go start, resA, green/red, resB, green/red, end
    Node startNode(WayPoint::start);
    currentNode = &startNode;

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
    SetPathLUT(WayPoint::start, WayPoint::resA, start_resA, sizeof(start_resA) / sizeof(start_resA[0]));
    // Serial.print("start to resA path: " + String(pathLUT[WayPoint::start][WayPoint::resA][0]) + ", " + String(pathLUT[WayPoint::start][WayPoint::resA][1]) + "\n");
} 

void Sequencer::GetNextPath(BlockType type, Path* path){
    WayPoint currentWayPoint = currentNode->GetWayPoint();
    Node* nextNode = currentNode->GetNext(type);
    WayPoint nextWayPoint = nextNode->GetWayPoint();

    //now need to get path from these start and end points
    Step* pathArray = GetPath(currentWayPoint, nextWayPoint);

    //delete the current node and set current to point to the next one
    delete currentNode;
    currentNode = nextNode;
    path->SetPath(pathArray, MAX_PATH_LENGTH);
    path->PrintPath();
}

Step* Sequencer::GetPath(WayPoint start, WayPoint end){
    return pathLUT[start][end];
}

void Sequencer::SetPathLUT(WayPoint start, WayPoint end, Step path[], int pathLength){
    for (int i = 0; i < pathLength; i++){
        pathLUT[start][end][i] = path[i];
    }
}