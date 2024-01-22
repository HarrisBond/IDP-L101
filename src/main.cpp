#include <Arduino.h>
#include "IO.h"
#include "StateMachine/LineFollowState.h"
#include "StateMachine/StateMachine.h"
#include "Sequencer.h"

StateMachine* stateMachine;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600); 
  Serial.println("Serial working, initializing");
  stateMachine = new StateMachine();
  // while (!Serial) yield();
  Sequencer::Initialize();
  stateMachine->ChangeState(LineFollowState::GetInstance());
}

// the loop function runs over and over again forever
void loop() {
  // stateMachine.ChangeState(LineFollowState::GetInstance());
  //calculate delta time somehow
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);    
  // stateMachine.Update();
  // delay(1000);                       // wait for a second
}