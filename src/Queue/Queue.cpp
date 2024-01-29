#include "Queue.h"
#include <Arduino.h>

Queue::Queue(int _maxSize){
    // steps = (Step*)malloc((maxSize + 1) * sizeof(Step));
    steps = new Step[_maxSize];
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
    
    // uint8_t dbarr[2];
    
    // Serial.println("steps[back] = " + String(steps[back]) + ", back = " + String(back));
    // unsigned addr = (unsigned) (&steps[back]);
    // dbarr[0] = (uint8_t)highByte((steps)>>8);
    // Serial.println("addr1: ");
    // Serial.println(addr); 
    back++;
    stepCount ++;
    // Serial.println("front = " + String(front));
    // Serial.println("back = " + String(back));
    // Serial.flush();
    // for (int i = front; i < back; i++){
    //     Serial.println("    queue [" + String(i) + "] = " + String(steps[i]));//   " + String(i) + "        + String(steps[i])
    //     Serial.flush();
    // }
    // Serial.println("steps[back-1] = " + String(steps[back-1]) + ", back-1 = " + String(back-1));
    // Serial.println("addr2: ");
    // addr = (unsigned) (&steps[back-1]);
    // dbarr[0] = (uint8_t)highByte((steps)>>8);
    // Serial.println(addr); 
    //Serial.println(String(steps));
    // Serial.println("queue push succesful");
    // Serial.flush();
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



