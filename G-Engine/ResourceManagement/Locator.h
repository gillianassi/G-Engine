#pragma once
#include "Audio/NullAudio.h"


class Locator
{
public:

    Locator() = delete;
    ~Locator() = delete;
    Locator(const Locator& other) = delete;
    Locator(Locator&& other) = delete;
    Locator& operator=(const Locator& other) = delete;
    Locator& operator=(Locator&& other) = delete;

    static AudioInterface& getAudio() { return *m_pAudioProvider; }

    static void provide(AudioInterface* service);

private:
    static AudioInterface* m_pAudioProvider;
    static NullAudio m_AudioNullProvider;

};