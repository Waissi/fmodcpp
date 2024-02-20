#ifndef _AUDIO_PLAYER_H
#define _AUDIO_PLAYER_H

#include <iostream>
#include "fmod_studio.hpp"

class AudioPlayer
{

public:
    ~AudioPlayer();
    static AudioPlayer *GetInstance();
    bool Update();
    bool SetListenerNumber(int number);

    FMOD::Studio::Bank *LoadBank(const char *bankName);
    bool UnloadBank(FMOD::Studio::Bank *bank);

    float GetGlobalParameter(const char *parameterName, bool final);
    bool SetGlobalParameter(const char *parameterName, float value, bool ignoreSeekSpeed);

    FMOD::Studio::Bus *GetBus(const char *busName);
    bool MuteBus(FMOD::Studio::Bus *bus, bool mute);
    bool IsBusMuted(FMOD::Studio::Bus *bus);
    bool SetBusVolume(FMOD::Studio::Bus *bus, float volume);
    float GetBusVolume(FMOD::Studio::Bus *bus);

    FMOD::Studio::VCA *GetVCA(const char *vcaName);
    bool SetVCAVolume(FMOD::Studio::VCA *vca, float volume);
    float GetVCAVolume(FMOD::Studio::VCA *vca);

    FMOD::Studio::EventInstance *GetEvent(const char *eventName);
    bool PlayOneShotEvent(const char *eventPath);
    bool StartEvent(FMOD::Studio::EventInstance *event);
    bool StopEvent(FMOD::Studio::EventInstance *event, bool fade);
    bool PauseEvent(FMOD::Studio::EventInstance *event, bool paused);
    bool IsEventPaused(FMOD::Studio::EventInstance *event);
    bool SetEventPosition(FMOD::Studio::EventInstance *event, int position);
    int GetEventPosition(FMOD::Studio::EventInstance *event);
    bool SetEventVolume(FMOD::Studio::EventInstance *event, float volume);
    float GetEventVolume(FMOD::Studio::EventInstance *event);
    bool SetListener3DAttributes(int listener, FMOD_3D_ATTRIBUTES *attributes, FMOD_VECTOR *attenuationPos);
    FMOD_3D_ATTRIBUTES GetListener3DAttributes(int listener);
    bool SetEvent3DAttributes(FMOD::Studio::EventInstance *event, FMOD_3D_ATTRIBUTES *attributes);
    FMOD_3D_ATTRIBUTES GetEvent3DAttributes(FMOD::Studio::EventInstance *event);
    float GetEventParameter(FMOD::Studio::EventInstance *event, const char *parameterName);
    bool SetEventParameter(FMOD::Studio::EventInstance *event, const char *parameterName, float value, bool ignoreSeekSpeed);

private:
    AudioPlayer();
    FMOD::Studio::System *studioSystem = nullptr;
};

#endif