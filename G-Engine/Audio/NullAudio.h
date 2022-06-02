#pragma once
#include "AudioInterface.h"

class NullAudio : public AudioInterface
{
public:
	NullAudio() = default;
	virtual ~NullAudio() = default;
	NullAudio(const NullAudio& other) = delete;
	NullAudio(NullAudio&& other) = delete;
	NullAudio& operator=(const NullAudio& other) = delete;
	NullAudio& operator=(NullAudio&& other) = delete;

	virtual void PlaySound(int, int) {}
	virtual int LoadSound(const std::string&) { return -1; }
	virtual void SetVolume(int, float) {}
	virtual float GetVolume(int) { return -1.f; }

	virtual void StopAllSounds(int) {}
	virtual void PauseAllSounds(int) {}
	virtual void ResumeAllSounds(int) {}
};