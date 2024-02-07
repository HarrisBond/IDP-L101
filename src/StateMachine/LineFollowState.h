#pragma once
#include "State.h"
#include "Paths/Path.h"
// #include "LineFollowing.h"


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
    const float timeSinceJunctionThreshold = 2000.0;
    void LineFollow(Step currentStep);
    void HandleBothOuters(Step currentSteo);
    void HandleBothInners(Step currentSteo);
    void HandleLightFlash();
    float nextStepTimer;
    float lightTimer;
    int sign(float x);
};
