#pragma once
#include <string>
class AudioInterface
{
public:
	virtual ~AudioInterface() = default;
	virtual void PlaySoundEffect(int soundID, int channel) = 0;
	virtual void StopAllSoundsEffects(int channel) = 0;
	virtual int LoadSoundEffect(const std::string& path) = 0;
};