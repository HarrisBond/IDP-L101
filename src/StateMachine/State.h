#pragma once

#include <Arduino.h>

class StateMachine;

//base class for states
class State {
public:
    virtual void EnterState(StateMachine* parentMachine);
    virtual void Update(StateMachine* parentMachine);
    virtual void ExitState(StateMachine* parentMachine);
    virtual ~State() {};
};