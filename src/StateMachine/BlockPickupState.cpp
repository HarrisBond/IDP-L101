#include "BlockPickupState.h"
#include <Arduino.h>
#include "BlindTurnState.h"
#include "StateMachine.h"
#include "../Sequencer.h"
#include "ReverseState.h"
#include "../Globals.h"

BlockPickupState::BlockPickupState(){

}

void BlockPickupState::EnterState(StateMachine* parentMachine){
  Serial.println("Block Pickup State entered");Serial.flush();
  // for (int _ = 0; _ < 5; _++){
  //   forwardTimerMilliseconds = 400;
  //   while (forwardTimerMilliseconds >= 0){
  //     LineFollow();
  //     forwardTimerMilliseconds -= time->GetDeltaTime();
  //   }
  //   motorController->SetRelativeSpeeds(-1.0, 0.0);
  //   delay(400);
  // }
  // Serial.println("done line following");
  // motorController->Forward();
  // float forwardTime = 1000;
  // while (forwardTime >= 0){
  //   forwardTime -= time->GetDeltaTime();
  //   if (IO::Sensors::PlatformSwitchPressed()){
  //     motorController->SetRelativeSpeeds(-1.0, 0.0);
  //     delay(400);
  //     break;
  //   }
  // }

  //go forward
  motorController->Forward();
  delay(300);
  motorController->Stop();
  motorController->LowerArm();
  //small reverse
  motorController->SetRelativeSpeeds(-0.4, 0.0);
  delay(100);
  motorController->Stop();
  //grab 1
  motorController->GripperClose();
  delay(3000);
  motorController->GripperOpen();
  delay(500);
  //small forward and reverse
  motorController->SetRelativeSpeeds(0.5, 0.0);
  delay(300);
  motorController->SetRelativeSpeeds(-0.4, 0.0);
  delay(100);
  motorController->Stop();
  //grab (double tap)
  motorController->GripperClose();
  delay(2500);
  //small reverse
  motorController->SetRelativeSpeeds(-0.5, 0);
  delay(600);
  //block test
  bool pressed = IO::Sensors::GripperSwitchPressed();
  motorController->Stop();
  motorController->RaiseArm();
  if (pressed){
    //solid
    digitalWrite(RED_LED_PIN, HIGH);
    delay(5000);
    digitalWrite(RED_LED_PIN, LOW);
    Sequencer::SetBlockType(BlockType::solid);
    parentMachine->ChangeState(ReverseState::GetInstance());return;
  } else {
    //foam
    digitalWrite(GREEN_LED_PIN, HIGH);
    delay(5000);
    digitalWrite(GREEN_LED_PIN, LOW);
    Sequencer::SetBlockType(BlockType::foam);
    parentMachine->ChangeState(ReverseState::GetInstance());return;
  }

}

void BlockPickupState::Update(StateMachine* parentMachine){
}

void BlockPickupState::LineFollow(){
  Serial.println("line following");
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

void BlockPickupState::ExitState(StateMachine* parentMachine){
}

State& BlockPickupState::GetInstance(){
    static BlockPickupState singleton;
    return singleton;
}

