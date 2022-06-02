#pragma once
#include <string>
class AudioInterface
{
public:
	virtual ~AudioInterface() = default;
	virtual void PlaySound(int soundID, int channel = -1) = 0;
	virtual int LoadSound(const std::string& path) = 0;
	virtual void SetVolume(int soundID, float fraction) = 0;
	virtual float GetVolume(int soundID) = 0;

	virtual void StopAllSounds(int channel = -1) = 0;
	virtual void PauseAllSounds(int channel = -1) = 0;
	virtual void ResumeAllSounds(int channel = -1) = 0;

};