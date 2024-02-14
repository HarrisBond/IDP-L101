#include "Path.h"

Path::Path() : path(20){

}

void Path::AddStep(Step newStep){
    path.Push(newStep);
}

void Path::SetPath(Step steps[], int numSteps){
    path.Flush();
    if (numSteps == 0 || steps == nullptr){
        return;
    }
    for (int i = 0; i < numSteps && steps[i] != Step::nullStep; i++){
        path.Push(steps[i]);
    }
}

Step Path::GetNextStep(){
    return path.Pop();
}

Step Path::GetCurrentStep(){
    return path.Peek();
}

Step Path::PeekNextStep(){
    return path.PeekNext();
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
        Serial.print(String(path.PeekAt(i)) + "  ");
        Serial.flush();
    }
    Serial.print("\n");
}


