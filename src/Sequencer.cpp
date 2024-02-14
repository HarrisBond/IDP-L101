#include "Sequencer.h"


Node* Sequencer::currentNode = nullptr;
Step* Sequencer::pathLUT[5][5];
BlockType Sequencer::currentBlockType = BlockType::empty;
bool Sequencer::started = false;
bool Sequencer::finishing = false;

void Sequencer::Initialize(){
    currentBlockType = BlockType::empty;
    started = false;
    finishing = false;
    for (unsigned int i = 0; i < sizeof(pathLUT) / sizeof(pathLUT[0]); i++){
        for (unsigned int j = 0; j < sizeof(pathLUT[0]) / sizeof(pathLUT[0][0]); j++){
            pathLUT[i][j] = nullptr;
        }
    }
    //initialize sequence tree
    //should go start, resA, green/red, resB, green/red, end
    currentNode = new Node(WayPoint::start);

    Node* resA = new Node(WayPoint::resA);
    resA->SetNextAngleIfSolid(-70);
    resA->SetNextAngleIfFoam(70);
    currentNode->SetNextIfEmpty(resA);

    Node* redSolidA = new Node(WayPoint::redSolid);
    redSolidA->SetNextAngleIfEmpty(-170);
    Node* greenFoamA = new Node(WayPoint::greenFoam);
    greenFoamA->SetNextAngleIfEmpty(170);
    resA->SetNextIfSolid(redSolidA);
    resA->SetNextIfFoam(greenFoamA);

    Node* resB = new Node(WayPoint::resB);
    resB->SetNextAngleIfSolid(70);
    resB->SetNextAngleIfFoam(-70);
    redSolidA->SetNextIfEmpty(resB);
    greenFoamA->SetNextIfEmpty(resB);

    Node* redSolidB = new Node(WayPoint::redSolid);
    redSolidB->SetNextAngleIfEmpty(-90);
    Node* greenFoamB = new Node(WayPoint::greenFoam);
    greenFoamB->SetNextAngleIfEmpty(90);
    resB->SetNextIfSolid(redSolidB);
    resB->SetNextIfFoam(greenFoamB);

    Node* industrialA = new Node(WayPoint::industrialA);
    industrialA->SetNextAngleIfFoam(90);
    industrialA->SetNextAngleIfSolid(90);
    redSolidB->SetNextIfEmpty(industrialA);
    greenFoamB->SetNextIfEmpty(industrialA);

    Node* redSolidC = new Node(WayPoint::redSolid);
    redSolidC->SetNextAngleIfEmpty(-170);
    Node* greenFoamC = new Node(WayPoint::greenFoam);
    greenFoamC->SetNextAngleIfEmpty(170);
    industrialA->SetNextIfFoam(greenFoamC);
    industrialA->SetNextIfSolid(redSolidC);

    // Node* end = new Node(WayPoint::start);
    // redSolidB->SetNextIfEmpty(end);
    // greenFoamB->SetNextIfEmpty(end);

    //all required paths are hard coded here and added to the lookup table
    //paths should only be added where the start waypoint is before the end in the waypoint enum
    //the corresponding reverse paths can then be generated and filled in algorithmically by 
    //iterating over the forward path backwards and reversing all turns.
    SetUpPathLUT();
}

bool Sequencer::HasStarted(){
    return started;
}

bool Sequencer::IsFinishing(){
    return finishing;
}

void Sequencer::GetNextPath(Path* path){
    started = true;
    WayPoint currentWayPoint = currentNode->GetWayPoint();
    Node* nextNode = currentNode->GetNext(currentBlockType);
    if (nextNode == nullptr){
        path->SetPath(nullptr, 0);
        return;
    } else if (nextNode->GetWayPoint() == WayPoint::start){
        finishing = true;
    }
    WayPoint nextWayPoint = nextNode->GetWayPoint();
    Serial.println("getting path from " + String(currentWayPoint) + " to " + String(nextWayPoint));

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

void Sequencer::SetBlockType(BlockType newType){
    currentBlockType = newType;
}

int Sequencer::GetNextTurnAngle(){
    return currentNode->GetNextTurnAngle(currentBlockType);
}

void Sequencer::SetUpPathLUT(){
    Step* start_resA = new Step[4] {Step::forwardLeft, Step::forwardRight, Step::forwardBlock, Step::nullStep};
    SetPathLUT(WayPoint::start, WayPoint::resA, start_resA);

    Step* resA_redSolid = new Step[4] {Step::forwardLeft, Step::forwardRight, Step::forwardPlatform, Step::nullStep};
    SetPathLUT(WayPoint::resA, WayPoint::redSolid, resA_redSolid);

    Step* resA_greenFoam = new Step[3] {Step::forwardLeft, Step::forwardPlatform, Step::nullStep};
    SetPathLUT(WayPoint::resA, WayPoint::greenFoam, resA_greenFoam);

    Step* redSolid_resB = new Step[4] {Step::forwardLeft, Step::forwardLeft, Step::forwardBlock, Step::nullStep};
    SetPathLUT(WayPoint::redSolid, WayPoint::resB, redSolid_resB);

    Step* greenFoam_resB = new Step[5] {Step::forwardRight, Step::forwardRight, Step::forwardRight, Step::forwardBlock, Step::nullStep};
    SetPathLUT(WayPoint::greenFoam, WayPoint::resB, greenFoam_resB);

    Step* resB_greenFoam = new Step[5] {Step::forwardLeft, Step::forwardLeft, Step::forwardRight, Step::forwardPlatform, Step::nullStep};
    SetPathLUT(WayPoint::resB, WayPoint::greenFoam, resB_greenFoam);

    Step* resB_redSolid = new Step[4] {Step::forwardRight, Step::forwardLeft, Step::forwardPlatform, Step::nullStep};
    SetPathLUT(WayPoint::resB, WayPoint::redSolid, resB_redSolid);

    Step* greenFoam_start = new Step[4] {Step::forwardRight, Step::forwardRight, Step::returnStart, Step::nullStep};
    SetPathLUT(WayPoint::greenFoam, WayPoint::start, greenFoam_start);

    Step* redSolid_start = new Step[3] {Step::forwardLeft, Step::returnStart, Step::nullStep};
    SetPathLUT(WayPoint::redSolid, WayPoint::start, redSolid_start);

    Step* redSolid_industrialA = new Step[4] {Step::forwardLeft, Step::forwardRight, Step::doIndustrialA, Step::nullStep};
    SetPathLUT(WayPoint::redSolid, WayPoint::industrialA, redSolid_industrialA);

    Step* greenFoam_industrialA = new Step[4] {Step::forwardRight, Step::forwardLeft, Step::doIndustrialA, Step::nullStep};
    SetPathLUT(WayPoint::greenFoam, WayPoint::industrialA, greenFoam_industrialA);

    Step* industrialA_redSolid = new Step[6] {Step::forwardLeft, Step::forwardLeft, Step::forwardRight, Step::forwardLeft, Step::forwardPlatform, Step::nullStep};
    SetPathLUT(WayPoint::industrialA, WayPoint::redSolid, industrialA_redSolid);

    //RLR
    Step* industrialA_greenFoam = new Step[5] {Step::forwardRight, Step::forwardLeft, Step::forwardRight, Step::forwardPlatform, Step::nullStep};
    SetPathLUT(WayPoint::industrialA, WayPoint::greenFoam, industrialA_greenFoam);
}

void Sequencer::SetPathLUT(WayPoint start, WayPoint end, Step* path){
    pathLUT[start][end] = path;
}
































// #include "Sequencer.h"
// #include <Arduino.h>

// Node* Sequencer::currentNode = nullptr;
// Step* Sequencer::pathLUT[5][5];
// BlockType Sequencer::currentBlockType = BlockType::empty;

// void Sequencer::Initialize(){
//     currentBlockType = BlockType::empty;
//     // Serial.println(String(int(sizeof(pathLUT) / sizeof(pathLUT[0]))));
//     // Serial.println(String(int(sizeof(pathLUT[0]) / sizeof(pathLUT[0][0]))));
//     // Serial.println(String(int(sizeof(pathLUT[0][0]) / sizeof(pathLUT[0][0][0]))));
//     for (unsigned int i = 0; i < sizeof(pathLUT) / sizeof(pathLUT[0]); i++){
//         for (unsigned int j = 0; j < sizeof(pathLUT[0]) / sizeof(pathLUT[0][0]); j++){
//             pathLUT[i][j] = nullptr;
//         }
//     }

//     //initialize sequence tree
//     //should go start, resA, green/red, resB, green/red, end
//     currentNode = new Node(WayPoint::start);

//     Node* resA = new Node(WayPoint::resA);
//     currentNode->SetNextIfEmpty(resA);

//     Node* redSolidA = new Node(WayPoint::redSolid);
//     Node* greenFoamA = new Node(WayPoint::greenFoam);
//     resA->SetNextIfSolid(redSolidA);
//     resA->SetNextIfFoam(greenFoamA);

//     Node* resB = new Node(WayPoint::resB);
//     redSolidA->SetNextIfEmpty(resB);
//     greenFoamA->SetNextIfEmpty(resB);

//     Node* redSolidB = new Node(WayPoint::redSolid);
//     Node* greenFoamB = new Node(WayPoint::greenFoam);
//     resB->SetNextIfSolid(redSolidB);
//     resB->SetNextIfFoam(greenFoamB);

//     Node* end = new Node(WayPoint::start);
//     redSolidB->SetNextIfEmpty(end);
//     greenFoamB->SetNextIfEmpty(end);

//     //all required paths are hard coded here and added to the lookup table
//     //paths should only be added where the start waypoint is before the end in the waypoint enum
//     //the corresponding reverse paths can then be generated and filled in algorithmically by 
//     //iterating over the forward path backwards and reversing all turns.
//     SetUpPathLUT();
// } 

// void Sequencer::GetNextPath(Path* path){
//     WayPoint currentWayPoint = currentNode->GetWayPoint();
//     Node* nextNode = currentNode->GetNext(currentBlockType);
//     WayPoint nextWayPoint = nextNode->GetWayPoint();
//     // std::cout << "getting path from " << currentWayPoint << " to " << nextWayPoint << "\n"; 

//     //now need to get path from these start and end points
//     Step* pathArray = GetPath(currentWayPoint, nextWayPoint);
//     // std::cout << pathArray[0] << ", " << pathArray[1] << ", " << pathArray[2] << "\n";
//     // Serial.println("pathArray & returns " + String(int(&pathArray)));
//     Serial.println("pathArray[0] = " + String(pathArray[0]));Serial.flush();
//     Serial.println("pathArray[1] = " + String(pathArray[1]));Serial.flush();
//     Serial.println("pathArray[2] = " + String(pathArray[2]));Serial.flush();
//     Serial.println("pathArray[3] = " + String(pathArray[3]));Serial.flush();

//     //delete the current node and set current to point to the next one
//     delete currentNode;
//     currentNode = nextNode;
//     path->SetPath(pathArray, MAX_PATH_LENGTH);
//     path->PrintPath();
// }

// Step* Sequencer::GetPath(WayPoint start, WayPoint end){
//     return pathLUT[start][end];
// }

// void Sequencer::SetBlockType(BlockType newType){
//     currentBlockType = newType;
// }

// void Sequencer::SetUpPathLUT(){
//     Step* start_resA = new Step[3] {Step::forwardLeft, Step::forwardRight, Step::forwardBlock};
//     SetPathLUT(WayPoint::start, WayPoint::resA, start_resA);

//     Step* resA_redSolid = new Step[4] {Step::forwardLeft, Step::forwardLeft, Step::forwardRight, Step::forwardPlatform};
//     SetPathLUT(WayPoint::resA, WayPoint::redSolid, resA_redSolid);

//     Step* resA_greenFoam = new Step[3] {Step::forwardRight, Step::forwardLeft, Step::forwardPlatform};
//     SetPathLUT(WayPoint::resA, WayPoint::greenFoam, resA_greenFoam);

//     Step* redSolid_resB = new Step[4] {Step::forwardRight, Step::forwardLeft, Step::forwardLeft, Step::forwardBlock};
//     SetPathLUT(WayPoint::redSolid, WayPoint::resB, redSolid_resB);

//     Step* greenFoam_resB = new Step[5] {Step::forwardLeft, Step::forwardRight, Step::forwardRight, Step::forwardRight, Step::forwardBlock};
//     SetPathLUT(WayPoint::greenFoam, WayPoint::resB, greenFoam_resB);

//     Step* resB_greenFoam = new Step[5] {Step::forwardLeft, Step::forwardLeft, Step::forwardLeft, Step::forwardRight, Step::forwardPlatform};
//     SetPathLUT(WayPoint::resB, WayPoint::greenFoam, resB_greenFoam);

//     Step* resB_redSolid = new Step[4] {Step::forwardRight, Step::forwardRight, Step::forwardLeft, Step::forwardPlatform};
//     SetPathLUT(WayPoint::resB, WayPoint::redSolid, resB_redSolid);

//     Step* greenFoam_start = new Step[3] {Step::forwardRight, Step::forwardRight, Step::forwardRight};
//     SetPathLUT(WayPoint::greenFoam, WayPoint::start, greenFoam_start);

//     Step* redSolid_start = new Step[2] {Step::forwardLeft, Step::forwardLeft};
//     SetPathLUT(WayPoint::redSolid, WayPoint::start, redSolid_start);

// }

// void Sequencer::SetPathLUT(WayPoint start, WayPoint end, Step* path){
//     //for (int i = 0; i < pathLength; i++){
//     pathLUT[start][end] = path;
//     //}
// }