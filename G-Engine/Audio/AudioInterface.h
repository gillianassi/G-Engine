#pragma once
#include <string>
class AudioInterface
{
public:
	virtual ~AudioInterface() {};
	virtual void PlaySound(int soundID) = 0;
	virtual void StopSound(int soundID) = 0;
	virtual void StopAllSounds() = 0;
	virtual int AddSound(const std::string& path) = 0;
};