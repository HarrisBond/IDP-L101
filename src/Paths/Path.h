#pragma once
#include "../Queue/Queue.h"
#include "../Globals.h"
#include <Arduino.h>

//stores a Step queue which represents the remaining steps to take to follow a path. These are generated
//by the sequencer object for use in the line follow state.

class Path{
    public:
        Path();
        void AddStep(Step newStep);
        void SetPath(Step steps[], int numSteps);
        Step GetNextStep();
        Step GetCurrentStep();
        Step PeekNextStep();
        bool IsEmpty();
        void PrintPath();
        int GetCount();
    private:
        Queue path;
};