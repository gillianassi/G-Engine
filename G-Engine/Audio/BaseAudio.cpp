#include "GEnginePCH.h"
#include "BaseAudio.h"
#include "SDL_mixer.h"


#include <unordered_map>
#include <map>
#include <mutex>
#include <queue>
#include <thread>

class SDLAudio final
{
public:
	SDLAudio(const std::string& filePath):
		m_pSoundChunk{ nullptr },
		m_FilePath{ filePath }
	{
	}

	~SDLAudio()
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
		else
		{
			// set the volume in case it has been set before it was loaded
			SetVolume(m_Volume);
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


		m_Volume = std::min(std::max(0,value), 128);
		if (m_pSoundChunk != nullptr)
		{
			Mix_VolumeChunk(m_pSoundChunk, value);
		}
	}

	int GetVolume() const
	{
		return m_Volume;
	}

	static void StopAll(int channel = -1)
	{
		Mix_HaltChannel(channel);
	}

	static void PauseAll(int channel)
	{
		Mix_Pause(channel);
	}
	static void ResumeAll(int channel)
	{
		Mix_Resume(channel);
	}

private:
	int m_Volume = 128;
	const std::string m_FilePath;
	Mix_Chunk* m_pSoundChunk;
};


class BaseAudio::AudioManagerImpl final
{
public:
	AudioManagerImpl()
	{
		Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, MIX_CHANNELS);

		// threading
		m_SoundThread = std::thread(&AudioManagerImpl::HandleSoundLoop, this);
	}
	~AudioManagerImpl()
	{

		// Lock to access the map
		std::unique_lock<std::mutex> lock(m_SoundMutex);
		for (IDAudioMap::iterator it = m_SoundMap.begin(); it != m_SoundMap.end();)
		{
			delete (*it).second;
			(*it).second = nullptr;
			it = m_SoundMap.erase(it);
		}
		lock.unlock();
		m_IsQuitting.store(true);
		// let the sound queue thread quit
		m_SoundQueueCV.notify_all();
		//Finish sound thread
		m_SoundThread.join();
		// close the audio
		Mix_CloseAudio();
	}

	void PlaySoundEffect(int soundID, int channel)
	{
		std::lock_guard<std::mutex> lockGuard(m_SoundMutex);
		IDAudioMap::iterator it = m_SoundMap.find(soundID);
		// does there exist a sound in the map with this ID
		if (it != m_SoundMap.end())
		{
			m_pPlayQueue.push(PlayRequest((*it).second, channel));
			//Notify sound thread that a change happened
			m_SoundQueueCV.notify_all();
		}
		else
		{
			std::cout << "Unregistered Sound with ID: " <<  std::to_string(soundID) << std::endl;
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
		m_IDMap[path] = m_NextFreeID;
		// add an unloaded soundeffect to the map
		m_SoundMap[m_NextFreeID] = new SDLAudio(path);
		// push it to the load queue
		m_pLoadQueue.push(m_SoundMap[m_NextFreeID]);
		// set the new free ID
		++m_NextFreeID;

		// notify the thread
		m_SoundQueueCV.notify_all();
		return m_NextFreeID - 1; // return the given Id
	}

	void SetVolume(int soundID, float fraction)
	{
		IDAudioMap::iterator it = m_SoundMap.find(soundID);
		if (it == m_SoundMap.end())
		{
			std::cout << "Warning: BaseAudio.cpp, SetVolume()" << std::to_string(soundID) << std::endl;
			std::cout << "No sound found with ID: " << std::to_string(soundID) << std::endl;
			return;
		}
		int SDLVolume = static_cast<int>(std::round(fraction * 128.f));
		(*it).second->SetVolume(SDLVolume);
		
	}

	float GetVolume(int soundID)
	{
		IDAudioMap::iterator it = m_SoundMap.find(soundID);
		if (it == m_SoundMap.end())
		{
			std::cout << "Warning: BaseAudio.cpp, GetVolume()" << std::to_string(soundID) << std::endl;
			std::cout << "No sound found with ID: " << std::to_string(soundID) << std::endl;
			return -1.f;
		}
		return (float((*it).second->GetVolume()) / 128.f);
	}


	void StopAllSoundsEffects(int channel)
	{
		SDLAudio::StopAll(channel);
	}

	void PauseAll(int channel)
	{
		SDLAudio::PauseAll(channel);
	}
	void ResumeAll(int channel)
	{
		SDLAudio::ResumeAll(channel);
	}


private:
	void HandleSoundLoop()
	{
		while (true)
		{
			std::unique_lock<std::mutex> lock(m_SoundMutex);
			m_SoundQueueCV.wait(lock, [&]() 
				{ 
					return !m_pLoadQueue.empty() || !m_pPlayQueue.empty() || m_IsQuitting.load(); 
				});

			if (m_IsQuitting.load())
			{
				lock.unlock();
				break;
			}
			if (!m_pPlayQueue.empty())
			{
				// Get the first sound effect to play from the queue
				PlayRequest soundRequest = m_pPlayQueue.front();
				//Pop front
				m_pPlayQueue.pop();
				//Unlock the lock
				lock.unlock();
				// Be sure that the sound is loaded before you play
				soundRequest._soundEffect->Load();
				// play the sound
				soundRequest._soundEffect->PlaySoundEffect(0, soundRequest._playChannel);
			}
			else if (!m_pLoadQueue.empty())
			{
				// Get the first sound effect to load from the queue
				SDLAudio* pSound = m_pLoadQueue.front();
				// Pop front
				m_pLoadQueue.pop();
				//Unlock the lock
				lock.unlock();
				//Do stuff
				pSound->Load();
			}
		}
	}

	// A struct of a combination of a sound effect and it's channel
	struct PlayRequest
	{
	public:
		PlayRequest(SDLAudio* soundEffect, int channel = -1):
			_soundEffect{ soundEffect },
			_playChannel{ channel }
		{}

		SDLAudio* _soundEffect;
		int _playChannel;
	};

	std::atomic<bool> m_IsQuitting = false;

	using IDAudioMap = std::map<int, SDLAudio*>;
	using PathIDMap = std::map<const std::string, int>;
	IDAudioMap m_SoundMap;
	PathIDMap m_IDMap;


	std::thread m_SoundThread;
	std::mutex m_SoundMutex;
	std::condition_variable m_SoundQueueCV;

	std::queue<PlayRequest> m_pPlayQueue;
	std::queue<SDLAudio*> m_pLoadQueue;


	int m_NextFreeID;
};


BaseAudio::BaseAudio():
	m_pImpl{ std::make_unique<AudioManagerImpl>() }
{
}

void BaseAudio::PlaySound(int soundID, int channel)
{
	m_pImpl->PlaySoundEffect(soundID, channel);
}


int BaseAudio::LoadSound(const std::string& path)
{
	return m_pImpl->LoadSoundEffect(path);
}

void BaseAudio::SetVolume(int sounID, float fraction)
{
	m_pImpl->SetVolume(sounID, fraction);
}

float BaseAudio::GetVolume(int sounID)
{
	return m_pImpl->GetVolume(sounID);
}


void BaseAudio::StopAllSounds(int channel)
{
	m_pImpl->StopAllSoundsEffects(channel);
}
void BaseAudio::PauseAllSounds(int channel)
{
	m_pImpl->PauseAll(channel);
}
void BaseAudio::ResumeAllSounds(int channel)
{
	m_pImpl->ResumeAll(channel);
}