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

    virtual void PlaySoundEffect(int soundID, int channel = -1);
    virtual void StopAllSoundsEffects(int channel = -1);
    // returns the Sound ID
    virtual int LoadSoundEffect(const std::string& path);

private:

    // implementation
    class AudioManagerImpl;
    std::unique_ptr<AudioManagerImpl> m_pImpl;
};
