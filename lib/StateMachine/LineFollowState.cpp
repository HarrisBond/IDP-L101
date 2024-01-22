#include "StateMachine.h"
#include <Arduino.h>
#include "IO.h"
#include "Path.h"
#include "Time.h"

LineFollowState::LineFollowState() : State() {
    Serial.println("line follow state constructor");
}

void LineFollowState::EnterState(StateMachine* parentMachine){
    //initialization
    Serial.println("Hello from the Line Follow State ");
}

void LineFollowState::Update(StateMachine* parentMachine) {
    Serial.println("Update fron the line follow state");
    timeSinceJunction += Time::GetDeltaTime();

    //need to check left and right sensors and turn accordingly.
    bool left = IO::Sensors::LineSenseLeft();
    bool right = IO::Sensors::LineSenseRight();

    float linearSpeed = IO::Motors::lineFollowLinearSpeed;
    float angularSpeed = IO::Motors::lineFollowAngularSpeed;
    if (left && !right){
        IO::Motors::SetRelativeSpeeds(linearSpeed, angularSpeed);//anticlockwise
    } else if (!left && right){
        IO::Motors::SetRelativeSpeeds(linearSpeed, -angularSpeed);//clockwise
    } else if (left && right){
        //t junction
        if (currentPath->GetCurrentStep() == Step::forwardLeft){
            //turn left
        } else if (currentPath->GetCurrentStep() == Step::forwardRight){
            //turn right
        }
        if (timeSinceJunction > timeSinceJunctionThreshold){
            //new junction detected
            Step nextStep = currentPath->GetNextStep();
            timeSinceJunction = 0.0;
        }
    } else {
        IO::Motors::SetRelativeSpeeds(linearSpeed, 0);//forward
    }

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