#include "StateMachine.h"
#include <Arduino.h>

void State::EnterState(StateMachine* parentMachine) {
    Serial.println("enter state called on state base class");
    Serial.flush();
}

void State::Update(StateMachine* parentMachine) {
    Serial.println("update called on state base class");
    Serial.flush();
}

void State::ExitState(StateMachine* parentMachine) {
    Serial.println("exit state called on state base class");
    Serial.flush();
}