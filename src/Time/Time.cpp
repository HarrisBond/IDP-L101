#include "Time.h"
#include <Arduino.h>

Time::Time() {
	//initialise
	Serial.println("time constructor called");Serial.flush();
	previousTime = millis();
	deltaTime = 0.0;
	Serial.println("End of time constructor");Serial.flush();
}

void Time::Update() {
	unsigned long currentTime = millis();
	deltaTime = currentTime - previousTime;
	previousTime = currentTime;
	//get current time, calculate and update deltatime, set current time
}

float Time::GetDeltaTime() {
	//return delta time
	return deltaTime;
}