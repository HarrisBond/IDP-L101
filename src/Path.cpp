#include "Path.h"

Path::Path() : path(sizeof(Step), 20, FIFO, false){
}

void Path::AddStep(Step newStep){
    path.push(&newStep);
}

Step Path::GetNext(){
    Step next;
    if (path.pop(&next)){
        return next;
    } else {
        return Step::null;
    }
}
