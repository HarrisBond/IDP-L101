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
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(GREEN_LED_PIN,OUTPUT);
  pinMode(RED_LED_PIN,OUTPUT);
  pinMode(INNER_LEFT_LINE_SENSOR_PIN, INPUT); // declare LED as output
  pinMode(INNER_RIGHT_LINE_SENSOR_PIN, INPUT); 
  pinMode(OUTER_LEFT_LINE_SENSOR_PIN, INPUT); 
  pinMode(OUTER_RIGHT_LINE_SENSOR_PIN, INPUT); 
  pinMode(CRASH_SENSOR_PIN, INPUT);
  pinMode(GRIPPER_SWITCH_PIN, INPUT);
  pinMode(START_BUTTON_PIN, INPUT);
  Serial.begin(9600); 
  while (!Serial) yield();
  Serial.println("Serial working, initializing");Serial.flush();
  time = new Time();
  motorController = new IO::Motors();
  motorController->Initialise();
  motorController->LowerArm();
  LineFollowState::GetInstance();
  // delay(1000);
  motorController->GripperClose();
  delay(3000);
  motorController->GripperStop();
  while(!IO::Sensors::StartSwitchPressed()){}
  stateMachine = new StateMachine();
  Sequencer::Initialize();
  stateMachine->ChangeState(BlindForwardState::GetInstance());
}

void loop() {
  time->Update();
  stateMachine->Update();
}