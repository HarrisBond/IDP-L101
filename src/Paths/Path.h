#pragma once
#include "../Queue/Queue.h"
#include "../Globals.h"
#include <Arduino.h>

//these store the direction bias. When a T Junction is reached, the bot will turn until both the
//left and right sensors detect the line. At this point, we can either turn left or right, which
//is determined by the left or right bias here.


class Path{
    public:
        Path();
        void AddStep(Step newStep);
        void SetPath(Step steps[], int numSteps);
        Step GetNextStep();
        Step GetCurrentStep();
        bool IsEmpty();
        void PrintPath();
        int GetCount();
    private:
        Queue path;
};