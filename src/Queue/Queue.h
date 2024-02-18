#pragma once
#include "../Globals.h"
#include <Arduino.h>


//a very simple custom queue class to store a queue of Steps, for use in path planning.
class Queue{
    public:
        Queue(int _maxSize);
        void Push(Step newStep);
        Step Pop();
        Step Peek();
        Step PeekAt(int index);
        Step PeekNext();
        void Flush();
        int GetCount();
    private:
        Step* steps;
        int front;
        int back;
        int maxSize;
        int stepCount;
};