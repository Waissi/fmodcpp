#include "audioPlayer.h"
static AudioPlayer *audioPlayer = nullptr;

/*
                                                                       SYSTEM
*/

AudioPlayer::AudioPlayer()
{
    FMOD_RESULT result = FMOD::Studio::System::create(&studioSystem, FMOD_VERSION);
    if (result != FMOD_OK)
        return;
    result = studioSystem->initialize(1200, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr);
    if (result != FMOD_OK)
        return;
    std::cout << "FMOD INIT"
              << "\n";
}

AudioPlayer::~AudioPlayer()
{
    FMOD_RESULT result = studioSystem->release();
    if (result != FMOD_OK)
        return;
    std::cout << "FMOD RELEASE"
              << "\n";
}

AudioPlayer *AudioPlayer::GetInstance()
{
    if (!audioPlayer)
        audioPlayer = new AudioPlayer();
    return audioPlayer;
}

bool AudioPlayer::Update()
{
    FMOD_RESULT result = studioSystem->update();
    return result == FMOD_OK;
}

bool AudioPlayer::SetListenerNumber(int _number)
{
    FMOD_RESULT result = studioSystem->setNumListeners(_number);
    return result == FMOD_OK;
}

/*
                                                                      BANKS
*/

FMOD::Studio::Bank *AudioPlayer::LoadBank(const char *bankName)
{
    FMOD::Studio::Bank *bank = nullptr;
    studioSystem->loadBankFile(bankName, FMOD_STUDIO_LOAD_BANK_NORMAL, &bank);
    return bank;
}

bool AudioPlayer::UnloadBank(FMOD::Studio::Bank *bank)
{
    FMOD_RESULT result = bank->unload();
    return result == FMOD_OK;
}

/*
                                                                      BUSES
*/

FMOD::Studio::Bus *AudioPlayer::GetBus(const char *busName)
{
    FMOD::Studio::Bus *bus;
    studioSystem->getBus(busName, &bus);
    return bus;
}

float AudioPlayer::GetBusVolume(FMOD::Studio::Bus *bus)
{
    float value, finalVolume;
    FMOD_RESULT result = bus->getVolume(&value, &finalVolume);
    if (result != FMOD_OK)
        return -1.0f;
    return finalVolume;
}

bool AudioPlayer::SetBusVolume(FMOD::Studio::Bus *bus, float volume)
{
    FMOD_RESULT result = bus->setVolume(volume);
    return result == FMOD_OK;
}

bool AudioPlayer::IsBusMuted(FMOD::Studio::Bus *bus)
{
    bool mute;
    FMOD_RESULT result = bus->getMute(&mute);
    if (result != FMOD_OK)
        return false;
    return mute;
}

bool AudioPlayer::MuteBus(FMOD::Studio::Bus *bus, bool mute)
{
    FMOD_RESULT result = bus->setMute(mute);
    return result == FMOD_OK;
}

/*
                                                                      VCAs
*/

FMOD::Studio::VCA *AudioPlayer::GetVCA(const char *vcaName)
{
    FMOD::Studio::VCA *vca = nullptr;
    studioSystem->getVCA(vcaName, &vca);
    return vca;
}

float AudioPlayer::GetVCAVolume(FMOD::Studio::VCA *vca)
{
    float value, finalVolume;
    FMOD_RESULT result = vca->getVolume(&value, &finalVolume);
    if (result != FMOD_OK)
        return -1.0f;
    return finalVolume;
}

bool AudioPlayer::SetVCAVolume(FMOD::Studio::VCA *vca, float volume)
{
    FMOD_RESULT result = vca->setVolume(volume);
    return result == FMOD_OK;
}

/*
                                                                      EVENTS
*/

FMOD::Studio::EventInstance *AudioPlayer::GetEvent(const char *eventName)
{
    FMOD::Studio::EventInstance *event = nullptr;
    FMOD::Studio::EventDescription *eventDescription = nullptr;
    studioSystem->getEvent(eventName, &eventDescription);
    eventDescription->createInstance(&event);
    return event;
}

float AudioPlayer::GetEventVolume(FMOD::Studio::EventInstance *event)
{
    float value, finalVolume;
    FMOD_RESULT result = event->getVolume(&value, &finalVolume);
    if (result != FMOD_OK)
        return -1.0f;
    return finalVolume;
}

bool AudioPlayer::SetEventVolume(FMOD::Studio::EventInstance *event, float volume)
{
    FMOD_RESULT result = event->setVolume(volume);
    return result == FMOD_OK;
}

int AudioPlayer::GetEventPosition(FMOD::Studio::EventInstance *event)
{
    int position;
    FMOD_RESULT result = event->getTimelinePosition(&position);
    if (result != FMOD_OK)
        return -1;
    return position;
}

bool AudioPlayer::SetEventPosition(FMOD::Studio::EventInstance *event, int position)
{
    FMOD_RESULT result = event->setTimelinePosition(position);
    return result == FMOD_OK;
}

bool AudioPlayer::PlayOneShotEvent(const char *eventPath)
{
    FMOD::Studio::EventInstance *event = nullptr;
    FMOD::Studio::EventDescription *eventDescription = nullptr;
    FMOD_RESULT result = studioSystem->getEvent(eventPath, &eventDescription);
    if (result != FMOD_OK)
        return false;
    result = eventDescription->createInstance(&event);
    if (result != FMOD_OK)
        return false;
    result = event->start();
    if (result != FMOD_OK)
        return false;
    result = event->release();
    return result == FMOD_OK;
}

bool AudioPlayer::StartEvent(FMOD::Studio::EventInstance *event)
{
    FMOD_RESULT result = event->start();
    return result == FMOD_OK;
}

bool AudioPlayer::StopEvent(FMOD::Studio::EventInstance *event, bool fade)
{
    if (fade)
    {
        FMOD_RESULT result = event->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);
        return result == FMOD_OK;
    }
    FMOD_RESULT result = event->stop(FMOD_STUDIO_STOP_IMMEDIATE);
    return result == FMOD_OK;
}

bool AudioPlayer::PauseEvent(FMOD::Studio::EventInstance *event, bool paused)
{
    FMOD_RESULT result = event->setPaused(paused);
    return result == FMOD_OK;
}

bool AudioPlayer::IsEventPaused(FMOD::Studio::EventInstance *event)
{
    bool paused;
    FMOD_RESULT result = event->getPaused(&paused);
    if (result != FMOD_OK)
        return false;
    return paused;
}

/*
                                                                3D ATTRIBUTES
*/

bool AudioPlayer::SetListener3DAttributes(int listener, FMOD_3D_ATTRIBUTES *attributes, FMOD_VECTOR *attenuationPosition)
{
    FMOD_RESULT result = studioSystem->setListenerAttributes(listener, attributes, attenuationPosition);
    return result == FMOD_OK;
}

FMOD_3D_ATTRIBUTES AudioPlayer::GetListener3DAttributes(int listener)
{
    FMOD_3D_ATTRIBUTES attributes;
    FMOD_VECTOR attenuationPosition;
    studioSystem->getListenerAttributes(listener, &attributes, &attenuationPosition);
    return attributes;
}

bool AudioPlayer::SetEvent3DAttributes(FMOD::Studio::EventInstance *event, FMOD_3D_ATTRIBUTES *attributes)
{
    FMOD_RESULT result = event->set3DAttributes(attributes);
    return result == FMOD_OK;
}

FMOD_3D_ATTRIBUTES AudioPlayer::GetEvent3DAttributes(FMOD::Studio::EventInstance *event)
{
    FMOD_3D_ATTRIBUTES attributes = FMOD_3D_ATTRIBUTES{};
    event->get3DAttributes(&attributes);
    return attributes;
}

/*
                                                                 PARAMETERS
*/

float AudioPlayer::GetEventParameter(FMOD::Studio::EventInstance *event, const char *parameterName)
{
    float value, finalValue;
    FMOD_RESULT result = event->getParameterByName(parameterName, &value, &finalValue);
    if (result != FMOD_OK)
        return -1.0f;
    return finalValue;
}

bool AudioPlayer::SetEventParameter(FMOD::Studio::EventInstance *event, const char *parameterName, float value, bool ignoreSeekSpeed)
{
    FMOD_RESULT result = event->setParameterByName(parameterName, value, ignoreSeekSpeed);
    return result == FMOD_OK;
}

float AudioPlayer::GetGlobalParameter(const char *parameterName, bool final)
{
    float value, finalValue;
    FMOD_RESULT result = studioSystem->getParameterByName(parameterName, &value, &finalValue);
    if (result != FMOD_OK)
        return -1.0f;
    return finalValue;
}

bool AudioPlayer::SetGlobalParameter(const char *parameterName, float value, bool ignoreSeekSpeed)
{
    FMOD_RESULT result = studioSystem->setParameterByName(parameterName, value, ignoreSeekSpeed);
    return result == FMOD_OK;
}
