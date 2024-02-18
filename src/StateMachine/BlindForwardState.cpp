#include "BlindForwardState.h"


BlindForwardState::BlindForwardState(){
    forwardTimerMilliseconds = 0.0;
}

void BlindForwardState::EnterState(StateMachine* parentMachine){
    lineFollowing = false;
    if (!Sequencer::HasStarted()){
        forwardTimerMilliseconds = startForwardTime;
    } else if (Sequencer::IsFinishing()){
        lineFollowing = true;
        lineFollowTime = endLineFollowTime;
        forwardTimerMilliseconds = endForwardTime;
    } else {
        forwardTimerMilliseconds = defaultForwardTime;
    }
    Serial.println("Blind Forward State Entered");Serial.flush();
    motorController->SetRelativeSpeeds(1.0, 0.0);
}

void BlindForwardState::Update(StateMachine* parentMachine){
    float deltaTime = time->GetDeltaTime();
    forwardTimerMilliseconds -= deltaTime;
    if (forwardTimerMilliseconds <= 0.0){
        motorController->Stop();
        parentMachine->ChangeState(LineFollowState::GetInstance());
        return;
    }
    if (lineFollowing){
        LineFollow();
        lineFollowTime -= deltaTime;
        if (lineFollowTime <= 0){
            lineFollowing = false;
            motorController->Forward();
        }
    }
}

void BlindForwardState::LineFollow(){
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

void BlindForwardState::ExitState(StateMachine* parentMachine){

}

State& BlindForwardState::GetInstance(){
    static BlindForwardState singleton;
    return singleton;
}
