#include "GEnginePCH.h"
#include "Locator.h"



NullAudio Locator::m_AudioNullProvider;
AudioInterface* Locator::m_pAudioProvider{ &m_AudioNullProvider };

void Locator::provide(AudioInterface* service)
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
