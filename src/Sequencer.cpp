#include "Sequencer.h"
#include <Arduino.h>

Node* Sequencer::currentNode = nullptr;
Step Sequencer::pathLUT[5][5][MAX_PATH_LENGTH];

void Sequencer::Initialize(){
    // pathLUT = new Step[5][5][MAX_PATH_LENGTH];
    Serial.println(String(int(sizeof(pathLUT) / sizeof(pathLUT[0]))));
    Serial.println(String(int(sizeof(pathLUT[0]) / sizeof(pathLUT[0][0]))));
    Serial.println(String(int(sizeof(pathLUT[0][0]) / sizeof(pathLUT[0][0][0]))));
    for (unsigned int i = 0; i < sizeof(pathLUT) / sizeof(pathLUT[0]); i++){
        for (unsigned int j = 0; j < sizeof(pathLUT[0]) / sizeof(pathLUT[0][0]); j++){
            for (unsigned int k = 0; k < sizeof(pathLUT[0][0]) / sizeof(pathLUT[0][0][0]); k++){
                pathLUT[i][j][k] = Step::nullStep;
            }
        }
    }
    // return;
    //initialize sequence tree
    //should go start, resA, green/red, resB, green/red, end
    Node* startNode = new Node(WayPoint::start);
    currentNode = startNode;

    Node* resA = new Node(WayPoint::resA);
    currentNode->SetNextIfEmpty(resA);

    Node* redSolidA = new Node(WayPoint::redSolid);
    Node* greenFoamA = new Node(WayPoint::greenFoam);
    resA->SetNextIfSolid(redSolidA);
    resA->SetNextIfFoam(greenFoamA);

    Node* resB = new Node(WayPoint::resB);
    redSolidA->SetNextIfEmpty(resB);
    greenFoamA->SetNextIfEmpty(resB);

    Node* redSolidB = new Node(WayPoint::redSolid);
    Node* greenFoamB = new Node(WayPoint::greenFoam);
    resB->SetNextIfSolid(redSolidB);
    resB->SetNextIfFoam(greenFoamB);

    Node* end = new Node(WayPoint::start);
    redSolidB->SetNextIfEmpty(end);
    greenFoamB->SetNextIfEmpty(end);

    //all required paths are hard coded here and added to the lookup table
    //paths should only be added where the start waypoint is before the end in the waypoint enum
    //the corresponding reverse paths can then be generated and filled in algorithmically by 
    //iterating over the forward path backwards and reversing all turns.
    Step start_resA[] = {Step::forwardLeft, Step::forwardRight, Step::forwardBlock};
    SetPathLUT(WayPoint::start, WayPoint::resA, start_resA, sizeof(start_resA) / sizeof(start_resA[0]));
    Step* start_resA_from_LUT = pathLUT[WayPoint::start][WayPoint::resA];
    Serial.println("start to resA path: " + String(start_resA_from_LUT[0]) + ", " + String(start_resA_from_LUT[1]) + ", " + String(start_resA_from_LUT[2]) + ", " + String(start_resA_from_LUT[3]));
} 

void Sequencer::GetNextPath(BlockType type, Path* path){
    WayPoint currentWayPoint = currentNode->GetWayPoint();
    Node* nextNode = currentNode->GetNext(type);
    WayPoint nextWayPoint = nextNode->GetWayPoint();

    //now need to get path from these start and end points
    Step* pathArray = GetPath(currentWayPoint, nextWayPoint);
    // Serial.println("pathArray & returns " + String(int(&pathArray)));
    Serial.println("pathArray[0] = " + String(pathArray[0]));Serial.flush();
    Serial.println("pathArray[1] = " + String(pathArray[1]));Serial.flush();
    Serial.println("pathArray[2] = " + String(pathArray[2]));Serial.flush();
    Serial.println("pathArray[3] = " + String(pathArray[3]));Serial.flush();

    //delete the current node and set current to point to the next one
    delete currentNode;
    currentNode = nextNode;
    path->SetPath(pathArray, MAX_PATH_LENGTH);
    path->PrintPath();
}

Step* Sequencer::GetPath(WayPoint start, WayPoint end){
    return &pathLUT[start][end][0];
}

void Sequencer::SetPathLUT(WayPoint start, WayPoint end, Step path[], int pathLength){
    for (int i = 0; i < pathLength; i++){
        pathLUT[start][end][i] = path[i];
    }
}