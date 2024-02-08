#include "Time.h"


Time::Time() {
	previousTime = millis();
	deltaTime = 0.0;
}

void Time::Update() {
	unsigned long currentTime = millis();
	deltaTime = currentTime - previousTime;
	previousTime = currentTime;
}

float Time::GetDeltaTime() {
	return deltaTime;
}