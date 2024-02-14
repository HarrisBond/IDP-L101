#pragma once
#include "../Globals.h"
#include <Arduino.h>

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