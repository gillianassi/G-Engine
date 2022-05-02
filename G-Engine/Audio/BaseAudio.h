#pragma once
#include "AudioInterface.h"
#include <map>

class BaseAudio final : public AudioInterface
{

public:

    BaseAudio();
    virtual ~BaseAudio() override;
    BaseAudio(const BaseAudio& other) = delete;
    BaseAudio(BaseAudio&& other) = delete;
    BaseAudio& operator=(const BaseAudio& other) = delete;
    BaseAudio& operator=(BaseAudio&& other) = delete;

    virtual void PlaySound(int soundID);
    virtual void StopSound(int soundID);
    virtual void StopAllSounds();
    // returns the Sound ID
    virtual int AddSound(const std::string& path);

private:
    // implementation
    int currentID;

    class SoundEffect;
    using IDAudioMap = std::map<int, SoundEffect*>;
    using PathIDMap = std::map<const std::string ,int>;
    IDAudioMap m_SoundMap;
    PathIDMap m_IDMap;
};
