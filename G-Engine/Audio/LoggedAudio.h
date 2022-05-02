#pragma once
#include <iostream>
#include "Audio.h"
class LoggedAudio : public Audio
{
public:
    LoggedAudio(Audio& wrapped)
        : wrapped_(wrapped)
    {}

    virtual ~LoggedAudio() = default;

    virtual void PlaySound(int soundID)
    {
        log("play sound: " + soundID);
        wrapped_.PlaySound(soundID);
    }

    virtual void StopSound(int soundID)
    {
        log("stop sound: " + soundID);
        wrapped_.StopSound(soundID);
    }

    virtual void StopAllSounds()
    {
        log("stop all sounds");
        wrapped_.StopAllSounds();
    }


    virtual int AddSound(const std::string& path)
    {

        int soundID = wrapped_.AddSound(path);
        log("Added Sound: " + path + " With ID: " + std::to_string(soundID));
        return soundID;
    }

private:
    void log(const std::string& message)
    {
        std::cout << message << std::endl;
    }

    Audio& wrapped_;
};
