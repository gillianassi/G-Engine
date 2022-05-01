#include "GEnginePCH.h"
#include "Time.h"


float Time::deltaTime = 0.f;
float Time::elapsedTime = 0.f;

Time::Time()
{
    StartFrameTime = std::chrono::high_resolution_clock::now();
}

void Time::HandleTimeCalculations()
{
    const auto currentTime = std::chrono::high_resolution_clock::now();
    deltaTime = std::chrono::duration<float>(currentTime - StartFrameTime).count();
    StartFrameTime = currentTime;
    elapsedTime += deltaTime;
}
