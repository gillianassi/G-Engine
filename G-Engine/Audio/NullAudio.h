#pragma once
#include "Audio.h"

class NullAudio : public Audio
{
public:
	NullAudio() = default;
	virtual ~NullAudio() = default;
	virtual void PlaySound(int) {}
	virtual void StopSound(int) {}
	virtual void StopAllSounds() {}
	virtual int AddSound(const std::string&) { return -1; }
};