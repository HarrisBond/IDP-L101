#include "Queue.h"

Queue::Queue(int _maxSize){
    steps = new Step[_maxSize];
    front = 0;
    back = 0;
    maxSize = _maxSize;
    stepCount = 0;
}

void Queue::Push(Step newStep){
    steps[back] = newStep;
    back++;
    stepCount ++;
}

Step Queue::Pop(){
    Step step = steps[front];
    front++;
    stepCount --;
    return step;
}

Step Queue::Peek(){
    return steps[front];
}

Step Queue::PeekAt(int index){
    return steps[index];
}

Step Queue::PeekNext(){
    return steps[front + 1];
}

void Queue::Flush(){
    stepCount = 0;
    front = 0;
    back = 0;
}

int Queue::GetCount(){
    return stepCount;
}



