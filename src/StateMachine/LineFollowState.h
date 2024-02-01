#pragma once
#include "State.h"
#include "Paths/Path.h"


class LineFollowState : public State {
public:
    LineFollowState();
    void EnterState(StateMachine* parentMachine);
    void Update(StateMachine* parentMachine);
    void ExitState(StateMachine* parentMachine);
    static State& GetInstance();
private:
    Path currentPath;
    float timeSinceJunction;
    const float timeSinceJunctionThreshold = 3000.0;
    void LineFollow(Step currentStep);
    void HandleBothOuters(Step currentSteo);
    void HandleBothInners(Step currentSteo);
    float nextStepTimer;
    int sign(float x);
};
