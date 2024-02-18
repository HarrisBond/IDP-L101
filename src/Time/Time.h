#pragma once
#include <Arduino.h>


//a basic time manager which gives the deltaTime between updates, used for timers throughout the codebase.
class Time {
public:
	Time();
	void Update();
	float GetDeltaTime();
private:
	float deltaTime;
	float previousTime;
};