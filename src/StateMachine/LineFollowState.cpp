#include "StateMachine.h"
#include "BlockPickupState.h"
#include "BlockDropState.h"
#include "BlindForwardState.h"
#include <Arduino.h>
#include "../IO/IO.h"
#include "../Paths/Path.h"
#include "../Time/Time.h"
#include "../Sequencer.h"
#include "../Globals.h"

LineFollowState::LineFollowState() : State() {
    timeSinceJunction = 0.0;
    // Serial.println("line follow state constructor");
    // Serial.flush();
}

void LineFollowState::EnterState(StateMachine* parentMachine){
    //initialization
    timeSinceJunction = 5000.0;
    nextStepTimer = -1.0;
    Sequencer::GetNextPath(&currentPath);
    if (currentPath.IsEmpty()){
        //empty path, we are done and at the start
        parentMachine->ChangeState()
    }
    Serial.println("Enter state called on line follow state, Current step is " + String(currentPath.GetCurrentStep()));
    Serial.flush();
}

void LineFollowState::Update(StateMachine* parentMachine) {
    Step currentStep = currentPath.GetCurrentStep();
    if (currentStep == Step::returnStart){
        parentMachine->ChangeState(BlindForwardState::GetInstance());
    }
    // Serial.println("    Update fron the line follow state, current step is " + String(currentPath.GetCurrentStep()));
    // Serial.flush();
    float deltaTime = time->GetDeltaTime();
    timeSinceJunction += deltaTime;
    float prevNextStepTimer = nextStepTimer;
    nextStepTimer -= deltaTime;
    if (sign(nextStepTimer) != sign(prevNextStepTimer)){
        currentPath.GetNextStep();
        // currentStep = currentPath.GetCurrentStep();
    }

    // int turnAngle = TurnAngleFromTurnStep(currentPath.GetCurrentStep());
    // if (turnAngle != 0){
    //     Sequencer::SetNextTurnAngle(turnAngle);
    //     currentPath.GetNextStep();
    // }
    // Serial.println(String());
    //need to check left and right sensors and turn accordingly.
    
    //if both sensors detect line, we are at a junction and need to choose turn direction
    //based on the path planning. also need to tell the state machine that a t junction has been reached.
    //this t junction will be continuously detected until we leave it, so a timer needs to be used by the
    //state machine before additional junction detections are accepted again.
    LineFollow(currentStep);

    //also need to check if we have reached the end of a line, eg before reaching a block or reaching the green/ red platform.
    //this will trigger changes to other states.
    if (currentStep == Step::forwardBlock){
        //check block distance sensor, enter block pickup state if needed
        float blockDistance;
        IO::Sensors::GetBlockDistance(blockDistance);
        if (blockDistance < BLOCK_DISTANCE_THRESHOLD){
            Serial.println("    Block detected");Serial.flush();
            parentMachine->ChangeState(BlockPickupState::GetInstance());
        }
        // BlockPickupState::GetInstance();
    }

    if (currentStep == Step::forwardPlatform){
        //check platform distance sensor, enter block drop state if needed
        if (IO::Sensors::PlatformSwitchPressed()){
            parentMachine->ChangeState(BlockDropState::GetInstance());
        }
    }
}

void LineFollowState::LineFollow(Step currentStep){
    // Serial.println(String(currentStep));
    // bool left = IO::Sensors::LineSenseLeft();
    // bool right = IO::Sensors::LineSenseRight();
    bool outerLeft, outerRight, innerLeft, innerRight;
    IO::Sensors::LineSense(outerLeft, outerRight, innerLeft, innerRight);
    // Serial.print(String(left) + ", " + String(right) + "\n");
    // Serial.flush();
    
    if (outerLeft && !outerRight){
        motorController->Left();//anticlockwise
    } else if (!outerLeft && outerRight){
        motorController->Right();//clockwise
    } else if (outerLeft && outerRight){
        HandleBothOuters(currentStep);
    } else {
        if (innerLeft && !innerRight){
            motorController->ForwardLeft();//anticlockwise
        } else if (!innerLeft && innerRight){
            motorController->ForwardRight();//clockwise
        } else if (innerLeft && innerRight){
            //should always turn left at junctions
            HandleBothInners(currentStep);
        } else {
            motorController->Forward();
        }
    }
}

void LineFollowState::HandleBothOuters(Step currentStep){
    // Serial.println("both outers");
    if (currentStep == Step::forwardBlock || currentStep == Step::forwardPlatform){
        motorController->Forward();
        return;
    }
    //t junction
    if (currentStep == Step::forwardLeft){
        motorController->Left();
    } else if (currentStep == Step::forwardRight){
        motorController->Right();
    } else if (currentStep == Step::returnStart){
        motorController->Forward();
        path->GetNextStep();
    }
    if (timeSinceJunction > timeSinceJunctionThreshold){
        //new junction detected
        // Step nextStep = currentPath->GetNextStep();
        Serial.println("    T junction found");Serial.flush();
        // currentPath.GetNextStep();
        // currentStep = currentPath.GetCurrentStep();
        timeSinceJunction = 0.0;
        nextStepTimer = timeSinceJunctionThreshold;
    }
}

void LineFollowState::HandleBothInners(Step currentStep){
    if (currentStep == Step::forwardLeft){
        motorController->ForwardLeft();
    } else if (currentStep == Step::forwardRight){
        motorController->ForwardRight();
    }
}

void LineFollowState::ExitState(StateMachine* parentMachine) {
    // Serial.println("Exiting the line follow state");
    // Serial.flush();
}

//this returns a singleton instance of the line follow state. A function like this needs to be included in each concrete state.
//these are used in state changes
State& LineFollowState::GetInstance() {
    static LineFollowState singleton;
    return singleton;
}

int LineFollowState::sign(float x){
    return x < 0 ? 0 : 1;
}