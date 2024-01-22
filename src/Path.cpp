#include "Path.h"

Path::Path() : path(sizeof(Step), 20, FIFO, false){
}

void Path::AddStep(Step newStep){
    path.push(&newStep);
}

void Path::SetPath(Step steps[]){
    path.flush();
    for (int i = 0; i < sizeof(steps) / sizeof(steps[0]); i++){
        path.push(&steps[i]);
    }
}

Step Path::GetNext(){
    Step next;
    if (path.pop(&next)){
        return next;
    } else {
        return Step::null;
    }
}


