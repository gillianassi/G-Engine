#pragma once
#include "AudioInterface.h"

class BaseAudio final : public AudioInterface
{

public:

    BaseAudio();
    virtual ~BaseAudio() override = default;
    BaseAudio(const BaseAudio& other) = delete;
    BaseAudio(BaseAudio&& other) = delete;
    BaseAudio& operator=(const BaseAudio& other) = delete;
    BaseAudio& operator=(BaseAudio&& other) = delete;

    virtual void PlaySound(int soundID, int channel = -1);
    virtual int LoadSound(const std::string& path);
    virtual void SetVolume(int soundID, float fraction);
    virtual float GetVolume(int soundID);


    virtual void StopAllSounds(int channel = -1);
    virtual void PauseAllSounds(int channel = -1);
    virtual void ResumeAllSounds(int channel = -1);
    // returns the Sound ID

private:

    // implementation
    class AudioManagerImpl;
    std::unique_ptr<AudioManagerImpl> m_pImpl;
};
