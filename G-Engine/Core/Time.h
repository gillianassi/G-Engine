#pragma once
#include "SingleInstance.h"
#include <chrono>

class Time final : SingleInstance<Time>
{
public:
	Time();
	virtual ~Time() = default;
	Time(const Time& other) = delete;
	Time(Time&& other) = delete;
	Time& operator=(const Time& other) = delete;
	Time& operator=(Time&& Timer) = delete;

	void HandleTimeCalculations();

	std::chrono::steady_clock::time_point GetStartFrame() { return StartFrameTime; };

	static float elapsedTime;
	static float deltaTime;
	static float fixedTimeStep;

private:

	std::chrono::steady_clock::time_point StartFrameTime;
};
