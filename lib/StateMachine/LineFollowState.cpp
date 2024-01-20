#include "StateMachine.h"
#include <Arduino.h>

LineFollowState::LineFollowState() : State() {
    Serial.println("line follow state constructor");
}

void LineFollowState::EnterState(StateMachine* parentMachine){
    //initialization
    Serial.println("Hello from the Line Follow State ");
}

void LineFollowState::Update(StateMachine* parentMachine) {
    Serial.println("Update fron the line follow state");
    //need to check left and right sensors and turn accordingly.

    //if both sensors detect line, we are at a junction and need to choose turn direction
    //based on the path planning. also need to tell the state machine that a t junction has been reached.
    //this t junction will be continuously detected until we leave it, so a timer needs to be used by the
    //state machine before additional junction detections are accepted again.

    //also need to check if we have reached the end of a line, eg before reaching a block or reaching the green/ red platform.
    //this will trigger changes to other states.
}

void LineFollowState::ExitState(StateMachine* parentMachine) {
    Serial.println("Exiting the line follow state");
}

//this returns a singleton instance of the line follow state. A function like this needs to be included in each concrete state.
//these are used in state changes
State& LineFollowState::GetInstance() {
    static LineFollowState singleton;
    return singleton;
}