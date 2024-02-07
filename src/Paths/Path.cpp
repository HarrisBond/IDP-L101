#include "Path.h"
#include <Arduino.h>
#include "../Globals.h"
#include ".//Queue/Queue.h"

Path::Path() : path(20){
    // Serial.println("initialized path, count = " + String(path.GetCount()));
    // Serial.flush();
}

void Path::AddStep(Step newStep){
    path.Push(newStep);
}

void Path::SetPath(Step steps[], int numSteps){
    path.Flush();
    if (numSteps == 0 || steps == nullptr){
        return;
    }
    // Serial.println("steps & returns " + String(int(&steps)));
    // Serial.print("Setting path, count = " + String(numSteps) + "\n");
    // Serial.flush();
    for (int i = 0; i < numSteps && steps[i] != Step::nullStep; i++){
        // Serial.println("  path adding " + String(steps[i]) + " to queue");
        // Serial.flush();
        path.Push(steps[i]);
    }
}

Step Path::GetNextStep(){
    // Step next;
    // if (!path.Pop()){
    //     return Step::nullStep;
    // }
    // return next;
    return path.Pop();
}

Step Path::GetCurrentStep(){
    // Step current;
    // if (!path.Peek(&current)){
    //     return Step::nullStep;
    // }
    // return current;
    return path.Peek();
}

bool Path::IsEmpty(){
    return path.GetCount()==0;
}

int Path::GetCount(){
    return path.GetCount();
}

void Path::PrintPath(){
    Serial.print("  printing path (count = " + String(path.GetCount()) + "): \n");
    Serial.flush();
    Serial.print("      ");
    for (int i = 0; i < path.GetCount(); i++){
        // Step currentStep;
        // path.PeekAt(&currentStep, i);
        Serial.print(String(path.PeekAt(i)) + "  ");
        Serial.flush();
    }
    Serial.print("\n");
}


