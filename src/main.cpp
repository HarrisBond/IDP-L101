#include <Arduino.h>
#include "IO/IO.h"
#include "StateMachine/BlindForwardState.h"
#include "StateMachine/StateMachine.h"
#include "Sequencer.h"
#include "Globals.h"
#include "SPI.h"

StateMachine* stateMachine;
Time* time;
IO::Motors* motorController;

void setup() {
  //initialize arduino pins
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(GREEN_LED_PIN,OUTPUT);
  pinMode(RED_LED_PIN,OUTPUT);
  pinMode(INNER_LEFT_LINE_SENSOR_PIN, INPUT);
  pinMode(INNER_RIGHT_LINE_SENSOR_PIN, INPUT); 
  pinMode(OUTER_LEFT_LINE_SENSOR_PIN, INPUT); 
  pinMode(OUTER_RIGHT_LINE_SENSOR_PIN, INPUT); 
  pinMode(CRASH_SENSOR_PIN, INPUT);
  pinMode(GRIPPER_SWITCH_PIN, INPUT);
  pinMode(START_BUTTON_PIN, INPUT);
  //initialise serial
  Serial.begin(9600); 
  while (!Serial) yield();
  Serial.println("Serial working, initializing");Serial.flush();
  //initialize time and motorController
  time = new Time();
  motorController = new IO::Motors();
  motorController->Initialise();
  //Put gripper into known position before program start
  motorController->LowerArm();
  LineFollowState::GetInstance();
  motorController->GripperClose();
  delay(3000);
  motorController->GripperStop();
  //wait for start button press
  while(!IO::Sensors::StartSwitchPressed()){}
  //create and initialize state machine
  stateMachine = new StateMachine();
  Sequencer::Initialize();
  stateMachine->ChangeState(BlindForwardState::GetInstance());
}

void loop() {
  time->Update();
  stateMachine->Update();
}