#pragma once
#include <Arduino.h>

class Time {
public:
	Time();
	void Update();
	float GetDeltaTime();
private:
	float deltaTime;
	float previousTime;
};