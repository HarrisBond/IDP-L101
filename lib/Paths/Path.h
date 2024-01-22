#pragma once
#include <cppQueue.h>

//these store the direction bias. When a T Junction is reached, the bot will turn until both the
//left and right sensors detect the line. At this point, we can either turn left or right, which
//is determined by the left or right bias here.
enum Step {forwardLeft, forwardRight, null};

class Path{
    public:
        Path();
        void AddStep(Step newStep);
        void SetPath(Step steps[]);
        Step GetNextStep();
        Step GetCurrentStep();
    private:
        cppQueue path;
};