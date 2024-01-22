#include "Path.h"
#include <Arduino.h>

Path::Path() : path(sizeof(Step), 20, FIFO, false){
}

void Path::AddStep(Step newStep){
    path.push(&newStep);
}

void Path::SetPath(Step steps[], int numSteps){
    path.flush();
    Serial.print("Setting path, count = " + String(numSteps) + "\n");
    Serial.flush();
    for (int i = 0; i < numSteps; i++){
        path.push(&steps[i]);
    }
}

Step Path::GetNextStep(){
    Step next;
    if (!path.pop(&next)){
        return Step::null;
    }
    return next;
}

Step Path::GetCurrentStep(){
    Step current;
    if (!path.peek(&current)){
        return Step::null;
    }
    return current;
}

void Path::PrintPath(){
    Serial.print("  printing path (count = " + String(path.getCount()) + "): \n");
    Serial.flush();
    for (unsigned int i = 0; i < path.getCount(); i++){
        Step currentStep;
        path.peekIdx(&currentStep, i);
        Serial.println("      " + String(currentStep));
        Serial.flush();
    }
}


