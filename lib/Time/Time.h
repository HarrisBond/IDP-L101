#pragma once

class Time {
public:
	Time();
	static void Update();
	static float GetDeltaTime();
private:
	static float deltaTime;
	static float previousTime;
};