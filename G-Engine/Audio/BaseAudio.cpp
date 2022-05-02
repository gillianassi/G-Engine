#include "GEnginePCH.h"
#include "BaseAudio.h"
#include "SDL_mixer.h"


class BaseAudio::SoundEffect
{
public:
	SoundEffect(const std::string& filename):
		m_pSoundChunk{ Mix_LoadWAV(filename.c_str()) }
	{
		if (m_pSoundChunk == nullptr)
		{
			std::string errorMsg = "SoundEffect: Unable to load " + filename + "\nSDL_mixer Error: " + Mix_GetError();
			std::cerr << errorMsg;
		}
	}
	~SoundEffect()
	{
		Mix_FreeChunk(m_pSoundChunk);
		m_pSoundChunk = nullptr;
	};

	bool IsLoaded() const
	{
		return m_pSoundChunk != nullptr;
	}

	bool PlaySound(int loops, int channel = -1)
	{
		if (m_pSoundChunk != nullptr)
		{
			if (Mix_PlayChannel(channel, m_pSoundChunk, loops) != -1)
			{
				return true;
			}
		}
		return false;
	}


	void SetVolume(int value)
	{
		if (m_pSoundChunk != nullptr)
		{
			Mix_VolumeChunk(m_pSoundChunk, value);
		}
	}

	int GetVolume() const
	{
		if (m_pSoundChunk != nullptr)
		{
			return Mix_VolumeChunk(m_pSoundChunk, -1);
		}
		else
		{
			return -1;
		}
	}

	void StopAll(int channel = -1)
	{
		Mix_HaltChannel(channel);
	}

	void PauseAll(int channel)
	{
		Mix_Pause(channel);
	}
	void ResumeAll(int channel)
	{
		Mix_Resume(channel);
	}

private:
	Mix_Chunk* m_pSoundChunk;
};



BaseAudio::BaseAudio():
	currentID{ 0 },
	m_SoundMap{},
	m_IDMap{}
{
}
BaseAudio::~BaseAudio()
{
	for (IDAudioMap::iterator it = m_SoundMap.begin(); it != m_SoundMap.end();)
	{
		delete (*it).second;
		(*it).second = nullptr;
		it = m_SoundMap.erase(it);
	}
}
void BaseAudio::PlaySound(int soundID)
{
	(*m_SoundMap.find(soundID)).second->PlaySound(0, -1);
}

void BaseAudio::StopSound(int soundID)
{
	(*m_SoundMap.find(soundID)).second->StopAll();
}

void BaseAudio::StopAllSounds()
{
	for (const auto&  sample : m_SoundMap)
	{
		sample.second->StopAll();
	}
}

int BaseAudio::AddSound(const std::string& path)
{
	if (m_IDMap.find(path) == m_IDMap.end())
	{
		m_IDMap[path] = currentID;
		m_SoundMap[currentID] = new SoundEffect(path);
		++currentID;
	}
	return m_IDMap[path];
}

