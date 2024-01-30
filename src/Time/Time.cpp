#include "Time.h"
#include <Arduino.h>

Time::Time() {
	//initialise
	previousTime = millis();
	deltaTime = 0.0;
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