#include <Arduino.h>
// #include "avr8-stub.h"
// #include "app_api.h"
#include "IO/IO.h"
#include "StateMachine/BlindForwardState.h"
#include "StateMachine/StateMachine.h"
#include "Sequencer.h"
#include "Globals.h"
#include "SPI.h"
#include <Servo.h>

StateMachine* stateMachine;
Time* time;
IO::Motors* motorController;
IO::TimeFlightSensor* timeFlightSensor;
Adafruit_DCMotor *grabberMotor;
Servo lifter; 

void setup() {
  // debug_init();
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(INNER_LEFT_LINE_SENSOR_PIN, INPUT); // declare LED as output
  pinMode(INNER_RIGHT_LINE_SENSOR_PIN, INPUT); 
  pinMode(OUTER_LEFT_LINE_SENSOR_PIN, INPUT); 
  pinMode(OUTER_RIGHT_LINE_SENSOR_PIN, INPUT); 
  Serial.begin(9600); 
  while (!Serial) yield();
  Serial.println("Serial working, initializing");Serial.flush();
  time = new Time();
  motorController = new IO::Motors();
  motorController->Initialise();
  timeFlightSensor->Initialise();
  stateMachine = new StateMachine();
  Sequencer::Initialize();
  stateMachine->ChangeState(BlindForwardState::GetInstance());
}

// the loop function runs over and over again forever
void loop() {
  // stateMachine.ChangeState(LineFollowState::GetInstance());
  //calculate delta time somehow
  // digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  // delay(1000);                       // wait for a second
  // digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  // delay(1000);    
  time->Update();
  stateMachine->Update();
  // delay(1000);                       // wait for a second
}