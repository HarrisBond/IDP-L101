#pragma once
class StateMachine;

class State {
public:
    virtual void EnterState(StateMachine* parentMachine);
    virtual void Update(StateMachine* parentMachine);
    virtual void ExitState(StateMachine* parentMachine);
    virtual ~State() {};
};