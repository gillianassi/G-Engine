#include "GEnginePCH.h"
#include "Time.h"


float Time::deltaTime = 0.f;
float Time::TotalElapsedTime = 0.f;
float Time::fixedTimeStep = 0.016f;

Time::Time():
    m_ForceElapsedUpperBound{true},
    m_ElapsedUpperBound{0.03f}
{
    StartFrameTime = std::chrono::high_resolution_clock::now();
}

void Time::HandleTimeCalculations()
{
    const auto currentTime = std::chrono::high_resolution_clock::now();
    deltaTime = std::chrono::duration<float>(currentTime - StartFrameTime).count();
    if (m_ForceElapsedUpperBound && deltaTime > m_ElapsedUpperBound)
    {
        deltaTime = m_ElapsedUpperBound;
    }
    
    StartFrameTime = currentTime;
    TotalElapsedTime += deltaTime;
}
