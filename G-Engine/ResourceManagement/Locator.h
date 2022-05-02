#pragma once
#include "Audio/Audio.h"
#include "Audio/NullAudio.h"

class Locator
{
public:
    static void initialize() { m_pAudioProvider = &m_AudioNullProvider; }

    static Audio& getAudio() { return *m_pAudioProvider; }

    static void provide(Audio* service)
    {
        if (service == nullptr)
        {
            // return adress as an insurrance that this will never be nullptr
            m_pAudioProvider = &m_AudioNullProvider;
        }
        else
        {
            m_pAudioProvider = service;
        }
    }

private:
    static Audio* m_pAudioProvider;
    static NullAudio m_AudioNullProvider;
};