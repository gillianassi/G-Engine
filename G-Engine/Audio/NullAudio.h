#pragma once
#include "AudioInterface.h"

class NullAudio : public AudioInterface
{
public:
	NullAudio() = default;
	virtual ~NullAudio() = default;
	virtual void PlaySoundEffect(int, int channel = -1) {}
	virtual void StopAllSoundsEffects(int channel = -1) {}
	virtual int LoadSoundEffect(const std::string&) { return -1; }
};