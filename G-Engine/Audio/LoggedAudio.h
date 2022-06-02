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

    LoggedAudio(const LoggedAudio& other) = delete;
    LoggedAudio(LoggedAudio&& other) = delete;
    LoggedAudio& operator=(const LoggedAudio& other) = delete;
    LoggedAudio& operator=(LoggedAudio&& other) = delete;

    virtual void PlaySound(int soundID,  int channel)
    {
        log("play sound: " + std::to_string(soundID) + "at channel: " + std::to_string(channel));
        wrapped_.PlaySound(soundID, channel);
    }


    virtual int LoadSound(const std::string& path)
    {

        log("Adding Sound: " + path);
        int soundID = wrapped_.LoadSound(path);
        log("Added Sound With ID: " + std::to_string(soundID));
        return soundID;
    }

    virtual void SetVolume(int soundID, float fraction)
    {
        log("Set sound volume sound to: " + std::to_string(fraction) + " of sound: " + std::to_string(soundID));
        wrapped_.SetVolume(soundID, fraction);
    };
    virtual float GetVolume(int soundID)
    {
        log("Get sound of sound: " + std::to_string(soundID));
        float vol = wrapped_.GetVolume(soundID);
        log("Volume fraction get: " + std::to_string(vol));
    };

    virtual void StopAllSounds(int channel = -1)
    {
        log("stop all sounds at channel: " + channel);
        wrapped_.StopAllSounds(channel);
    }

    virtual void PauseAllSounds(int channel = -1)
    {
        log("pause all sounds at channel: " + channel);
        wrapped_.PauseAllSounds(channel);
    }
    virtual void ResumeAllSounds(int channel = -1)
    {
        log("resume all sounds at channel: " + channel);
        wrapped_.ResumeAllSounds(channel);
    }

private:
    void log(const std::string& message)
    {
        std::cout << message << std::endl;
    }

    AudioInterface& wrapped_;
};
