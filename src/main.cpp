// #include <Arduino.h>

// // put function declarations here:
// int myFunction(int, int);

// void setup() {
//   // put your setup code here, to run once:
//   int result = myFunction(2, 3);
// }

// void loop() {
//   // put your main code here, to run repeatedly:
// }

// // put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }

#include <Arduino.h>
#include "IO.h"
#include "LineFollowState.h"
#include "StateMachine.h"

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600); 
}

// the loop function runs over and over again forever
void loop() {
  StateMachine stateMachine;
  stateMachine.ChangeState(LineFollowState::GetInstance());
  stateMachine.ChangeState(LineFollowState::GetInstance());
  while (true){
    //calculate delta time somehow
    stateMachine.Update();
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);                       // wait for a second
    Serial.print("serial works!\n");
    IO::LEDs::IndicateFoamBlock();
  }
}