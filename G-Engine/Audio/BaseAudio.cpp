#include "GEnginePCH.h"
#include "BaseAudio.h"
#include "SDL_mixer.h"


#include <unordered_map>
#include <map>
#include <mutex>
#include <queue>
#include <thread>

class SoundEffect final
{
public:
	SoundEffect(const std::string& filePath):
		m_pSoundChunk{ nullptr },
		m_FilePath{ filePath }
	{
	}

	~SoundEffect()
	{
		Mix_FreeChunk(m_pSoundChunk);
		m_pSoundChunk = nullptr;
	};


	void Load()
	{
		m_pSoundChunk = Mix_LoadWAV(m_FilePath.c_str());

		if (m_pSoundChunk == nullptr)
		{
			std::string errorMsg = "SoundEffect: Unable to load " + m_FilePath + "\nSDL_mixer Error: " + Mix_GetError();
			std::cerr << errorMsg;
		}
	}

	bool IsLoaded() const
	{
		return m_pSoundChunk != nullptr;
	}

	// -1 = first free unreserved channel
	bool PlaySoundEffect(int loops, int channel = -1)
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
	const std::string m_FilePath;
	Mix_Chunk* m_pSoundChunk;
};


class BaseAudio::AudioManagerImpl final
{
public:
	AudioManagerImpl()
	{
		Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, MIX_CHANNELS);
	}
	~AudioManagerImpl()
	{
		for (IDAudioMap::iterator it = m_SoundMap.begin(); it != m_SoundMap.end();)
		{
			delete (*it).second;
			(*it).second = nullptr;
			it = m_SoundMap.erase(it);
		}
		Mix_CloseAudio();
	}

	void PlaySoundEffect(int soundID, int channel)
	{
		(*m_SoundMap.find(soundID)).second->PlaySoundEffect(0, channel);
	}

	void StopAllSoundsEffects(int channel)
	{
		for (const auto& sample : m_SoundMap)
		{
			sample.second->StopAll();
		}
	}

	int LoadSoundEffect(const std::string& path)
	{
		//Lock queue
		std::lock_guard<std::mutex> lockGuard(m_SoundMutex);

		if (m_IDMap.find(path) != m_IDMap.end())
		{
			return m_IDMap[path];
		}
		//m_SoundMap[nextFreeID] = new SoundEffect(path);
		// add It to the path map but do not load it yet
		m_IDMap[path] = nextFreeID;
		// add an unloaded soundeffect to the map
		m_SoundMap[nextFreeID] = new SoundEffect(path);
		// push it to the load queue
		m_pLoadQueue.push(m_SoundMap[nextFreeID]);
		// set the new free ID
		++nextFreeID;

		// notify the thread
		m_SoundQueueCV.notify_all();
		return nextFreeID - 1; // return the given Id
	}


private:
	void HandleSoundLoop()
	{
		while (true)
		{
			std::unique_lock<std::mutex> lock(m_SoundMutex);
			// prioritize playing sounds
			do
			{
				if (!m_pPlayQueue.empty())
				{
					// Get the first sound effect to play from the queue
					SoundEffect* pSound = m_pPlayQueue.front();
					//Pop front
					m_pPlayQueue.pop();

					//Unlock the lock
					lock.unlock();

					//Do stuff
					pSound->Load();
					// how to give the channel?
					// ---------------------------------------------------------------------------------
					// struct? pointer - channel struct
					// 
					pSound->PlaySoundEffect(0);
				}

			} while (!m_pPlayQueue.empty());

			if (!m_pLoadQueue.empty())
			{
				// Get the first sound effect to load from the queue
				SoundEffect* pSound = m_pLoadQueue.front();
				// Pop front
				m_pLoadQueue.pop();

				//Unlock the lock
				lock.unlock();

				//Do stuff
				pSound->Load();
			}

			// if both the load queue and play queue are empty after this, wait for a new notify
			if (!m_pLoadQueue.empty() && !m_pPlayQueue.empty())
			{
				m_SoundQueueCV.wait(lock);
			}
		}
	}

	using IDAudioMap = std::map<int, SoundEffect*>;
	using PathIDMap = std::map<const std::string, int>;
	IDAudioMap m_SoundMap;
	PathIDMap m_IDMap;


	std::thread m_SoundThread;
	std::mutex m_SoundMutex;
	std::condition_variable m_SoundQueueCV;

	std::queue<SoundEffect*> m_pPlayQueue;
	std::queue<SoundEffect*> m_pLoadQueue;


	int nextFreeID;
};


BaseAudio::BaseAudio():
	m_pImpl{ std::make_unique<AudioManagerImpl>() }
{
}

void BaseAudio::PlaySoundEffect(int soundID, int channel)
{
	m_pImpl->PlaySoundEffect(soundID, channel);
}
void BaseAudio::StopAllSoundsEffects(int channel)
{
	m_pImpl->StopAllSoundsEffects(channel);
}

int BaseAudio::LoadSoundEffect(const std::string& path)
{
	return m_pImpl->LoadSoundEffect(path);
}