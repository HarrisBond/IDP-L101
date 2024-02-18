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

  //the double tap here is used to improve reliability when picking up blocks: the first grab
  //aligns the block with the robot which makes the second grab (when testing is done) more reliable
  //this eliminates edge cases where grabbing the diagonal of a block causes misses and false readings


  //go forward
  motorController->Forward();
  delay(400);
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

void BlockPickupState::ExitState(StateMachine* parentMachine){
}

State& BlockPickupState::GetInstance(){
    static BlockPickupState singleton;
    return singleton;
}

