#include "Queue.h"
#include <Arduino.h>

Queue::Queue(int _maxSize){
    steps = (Step*)malloc(maxSize * sizeof(Step));
    front = 0;
    back = 0;
    maxSize = _maxSize;
    stepCount = 0;
    Serial.println("queue constructor called, count = " + String(stepCount) + ", max size = " + String(maxSize));
    Serial.flush();
}

void Queue::Push(Step newStep){
    // Serial.println("Queue push called, adding " + String(newStep));
    Serial.flush();
    steps[back] = newStep;
    Serial.println("added new item");
    Serial.flush();
    back++;
    Serial.println("incremented back");
    Serial.flush();
    stepCount ++;
    Serial.println("incremented step count");
    Serial.flush();
    // Serial.println("Adding step to queue: " + String(newStep) + ", incrementing queue count, new count = ");
    Serial.flush();
    Serial.println("front = " );//+ String(front)
    // Serial.println("back = " + String(back));
    Serial.flush();
    for (int i = front; i < back; i++){
        Serial.println("    queue [] = ");//   " + String(i) + "        + String(steps[i])
        Serial.flush();
    }
    Serial.println("queue push succesful");
    Serial.flush();
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
    front = 0;
    back = 0;
}

int Queue::GetCount(){
    return stepCount;
}



