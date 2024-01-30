#include "Queue.h"
#include <Arduino.h>

Queue::Queue(int _maxSize){
    // steps = (Step*)malloc((maxSize + 1) * sizeof(Step));
    steps = new Step[_maxSize];
    front = 0;
    back = 0;
    maxSize = _maxSize;
    stepCount = 0;
    // Serial.println("queue constructor called, count = " + String(stepCount) + ", max size = " + String(maxSize));
    // Serial.flush();
}

void Queue::Push(Step newStep){
    steps[back] = newStep;
    back++;
    stepCount ++;
    // Serial.println("        " + String(stepCount));
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

void Queue::Flush(){
    stepCount = 0;
    front = 0;
    back = 0;
}

int Queue::GetCount(){
    return stepCount;
}



