#include "Queue.h"
#include <Arduino.h>

Queue::Queue(int _maxSize){
    steps = (Step*)malloc(maxSize * sizeof(Step));
    front = steps;
    back = steps;
    maxSize = _maxSize;
    stepCount = 0;
    Serial.println("queue constructor called, count = " + String(stepCount));
    Serial.flush();
}

void Queue::Push(Step newStep){
    *front = newStep;
    front++;
    Serial.println("incrementing queue count, count = " + String(stepCount));
    Serial.flush();
    stepCount ++;
}

Step Queue::Pop(){
    Step step = *back;
    back++;
    stepCount --;
    return step;
}

Step Queue::Peek(){
    return *back;
}

Step Queue::PeekAt(int index){
    return steps[index];
}

void Queue::Flush(){
    front = steps;
    back = steps;
}

int Queue::GetCount(){
    return stepCount;
}



