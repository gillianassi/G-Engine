#pragma once
#include <iostream>
#include "AudioInterface.h"
class LoggedAudio : public AudioInterface
{
public:
    LoggedAudio(AudioInterface& wrapped)
        : wrapped_(wrapped)
    {}

    virtual ~LoggedAudio() = default;

    virtual void PlaySoundEffect(int soundID,  int channel)
    {
        log("play sound: " + std::to_string(soundID) + "at channel: " + std::to_string(channel));
        wrapped_.PlaySoundEffect(soundID, channel);
    }

    virtual void StopAllSoundsEffects(int channel = -1)
    {
        log("stop all sounds at channel: " + channel);
        wrapped_.StopAllSoundsEffects(channel);
    }


    virtual int LoadSoundEffect(const std::string& path)
    {

        int soundID = wrapped_.LoadSoundEffect(path);
        log("Added Sound: " + path + " With ID: " + std::to_string(soundID));
        return soundID;
    }

private:
    void log(const std::string& message)
    {
        std::cout << message << std::endl;
    }

    AudioInterface& wrapped_;
};
