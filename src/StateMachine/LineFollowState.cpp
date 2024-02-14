#include "LineFollowState.h"


LineFollowState::LineFollowState() : State() {
    timeSinceJunction = 0.0;
    DFRobot_VL53L0X TOFsensor;
    TOFsensor.begin(0x50);
    TOFsensor.setMode(TOFsensor.eContinuous,TOFsensor.eHigh);
    TOFsensor.start();


}

void LineFollowState::EnterState(StateMachine* parentMachine){
    timeSinceJunction = 5000.0;
    nextStepTimer = -1.0;
    forwardBlockTimer = 10000000;
    Sequencer::GetNextPath(&currentPath);
    Serial.println("current path count = " + String(currentPath.GetCount()));
    if (currentPath.IsEmpty()){
        //empty path, we are done and at the start
        Serial.println("empty path detected");Serial.flush();
        digitalWrite(BLUE_LED_PIN, LOW);
        parentMachine->ChangeState(FinishedState::GetInstance());
        return;
    }
    Serial.println("Enter state called on line follow state, Current step is " + String(currentPath.GetCurrentStep()));
    Serial.flush();
}

void LineFollowState::Update(StateMachine* parentMachine) {
    Step currentStep = currentPath.GetCurrentStep();
    if (currentStep == Step::returnStart){
        digitalWrite(BLUE_LED_PIN, LOW);
        parentMachine->ChangeState(BlindForwardState::GetInstance());
        return;
    }
    float deltaTime = time->GetDeltaTime();
    timeSinceJunction += deltaTime;
    lightTimer += deltaTime;
    float prevNextStepTimer = nextStepTimer;
    nextStepTimer -= deltaTime;
    forwardBlockTimer -= deltaTime;
    if (sign(nextStepTimer) != sign(prevNextStepTimer)){
        currentPath.GetNextStep();
        if (currentPath.GetCurrentStep() == Step::forwardPlatform){
            motorController->LowerArm();
        } else if (currentPath.GetCurrentStep() == Step::forwardBlock){
            // motorController->GripperOpen();
            // motorController->Stop();
            // delay(1000);
            // for (int _ = 0; _ < 5; _++){
            //     float forwardTimerMilliseconds = 400.0;
            //     while (forwardTimerMilliseconds >= 0){
            //         OtherLineFollow();
            //         forwardTimerMilliseconds -= time->GetDeltaTime();
            //     }
            //     float reverseTimerMilliseconds = 400.0;
            //     while (reverseTimerMilliseconds >= 0){
            //         OtherLineFollowReverse();
            //         reverseTimerMilliseconds -= time->GetDeltaTime();
            //     }
            //     // motorController->SetRelativeSpeeds(-1.0, 0.0);
            //     // delay(400);
            // }
            motorController->GripperOpen();
            forwardBlockTimer = 4000;
        }
        if (currentPath.PeekNextStep() == Step::forwardBlock){

        }
    }
    HandleLightFlash();

    //if both sensors detect line, we are at a junction and need to choose turn direction
    //based on the path planning. also need to tell the state machine that a t junction has been reached.
    //this t junction will be continuously detected until we leave it, so a timer needs to be used by the
    //state machine before additional junction detections are accepted again.
    LineFollow(currentStep);

    //also need to check if we have reached the end of a line, eg before reaching a block or reaching the green/ red platform.
    //this will trigger changes to other states.
    if (currentStep == Step::forwardBlock){
        //check block distance sensor, enter block pickup state if needed
        float blockDistance = TOFsensor.getDistance();
        // Serial.println(String(blockDistance));
        if (blockDistance < BLOCK_DISTANCE_THRESHOLD || forwardBlockTimer <= 0){
            Serial.println("    Block detected");Serial.flush();
            digitalWrite(BLUE_LED_PIN, LOW);
            parentMachine->ChangeState(BlockPickupState::GetInstance());
            return;
        }
    }

    if (currentStep == Step::forwardPlatform){
        //check platform distance sensor, enter block drop state if needed
        if (IO::Sensors::PlatformSwitchPressed()){
            digitalWrite(BLUE_LED_PIN, LOW);
            parentMachine->ChangeState(BlockDropState::GetInstance());
            return;
        }
    }
}

void LineFollowState::OtherLineFollow(){
    // Serial.println("line following");
    if (IO::Sensors::PlatformSwitchPressed()){
        motorController->SetRelativeSpeeds(-1.0, 0.0);
        delay(200);return;
    }
    bool outerLeft, outerRight, innerLeft, innerRight;
    IO::Sensors::LineSense(outerLeft, outerRight, innerLeft, innerRight);
    
    if (outerLeft && !outerRight){
        motorController->Left();//anticlockwise
    } else if (!outerLeft && outerRight){
        motorController->Right();//clockwise
    } else if (outerLeft && outerRight){
        motorController->Forward();
    } else {
        if (innerLeft && !innerRight){
            motorController->SetRelativeSpeeds(0.7, 0.4);//anticlockwise
        } else if (!innerLeft && innerRight){
            motorController->SetRelativeSpeeds(0.7, -0.4);//clockwise
        } else if (innerLeft && innerRight){
            motorController->Forward();
        } else {
            motorController->Forward();
        }
    }
}

void LineFollowState::OtherLineFollowReverse(){
    // Serial.println("line following");
    bool outerLeft, outerRight, innerLeft, innerRight;
    IO::Sensors::LineSense(outerLeft, outerRight, innerLeft, innerRight);
    
    if (outerLeft && !outerRight){
        motorController->SetSpeeds(0.0, -1.0);
    } else if (!outerLeft && outerRight){
        motorController->SetSpeeds(-1.0, 0.0);
    } else if (outerLeft && outerRight){
        motorController->SetSpeeds(-1.0, -1.0);
    } else {
        if (innerLeft && !innerRight){
            motorController->SetRelativeSpeeds(-0.6, -1.0);//anticlockwise
        } else if (!innerLeft && innerRight){
            motorController->SetRelativeSpeeds(-1.0, -0.6);//clockwise
        } else {
            motorController->SetRelativeSpeeds(-1.0, -1.0);
        }
    }
}

void LineFollowState::LineFollow(Step currentStep){
    bool outerLeft, outerRight, innerLeft, innerRight;
    IO::Sensors::LineSense(outerLeft, outerRight, innerLeft, innerRight);
    
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
        currentPath.GetNextStep();
    }
    if (timeSinceJunction > timeSinceJunctionThreshold){
        Serial.println("    T junction found");Serial.flush();
        timeSinceJunction = 0.0;
        nextStepTimer = timeSinceJunctionThreshold;
        // if (currentPath.PeekNextStep() == Step::forwardBlock){
        //     motorController->GripperOpen();
        // }
    }
}

void LineFollowState::HandleLightFlash(){
    if (lightTimer >= 500){
        //toggle blue LED
        IO::LEDs::ToggleBlueLED();
        lightTimer=0.0;
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