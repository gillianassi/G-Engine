#pragma once
#include "AudioInterface.h"

class NullAudio : public AudioInterface
{
public:
	NullAudio() = default;
	virtual ~NullAudio() = default;
	virtual void PlaySound(int) {}
	virtual void StopSound(int) {}
	virtual void StopAllSounds() {}
	virtual int AddSound(const std::string&) { return -1; }
};