#include "AudioSystem.h"

#include "AudioClip.h"

namespace viper {
    /// <summary>
    /// Checks if an FMOD operation was successful and logs an error if it was not.
    /// </summary>
    /// <param name="result">The FMOD_RESULT value returned by an FMOD operation.</param>
    /// <returns>True if the result indicates success (FMOD_OK); false otherwise.</returns>
    bool AudioSystem::CheckFMODResult(FMOD_RESULT result) {
        if (result != FMOD_OK) {
            Logger::Error("FMOD_ErrorString: {}", FMOD_ErrorString(result));
            return false;
        }
        return true;
    }

    /// <summary>
    /// Initializes the audio system using FMOD.
    /// </summary>
    /// <returns>Returns true if the audio system was successfully initialized; otherwise, returns false.</returns>
    bool AudioSystem::Initialize() {
        FMOD_RESULT result = FMOD::System_Create(&_system);

        if (!CheckFMODResult(result)) return false;

        void* extradriverdata = nullptr;

        if (!CheckFMODResult(result)) return false;

        result = _system->init(32, FMOD_INIT_NORMAL, extradriverdata);

        return true;
    }

    /// <summary>
    /// Shuts down the audio system and releases associated resources.
    /// </summary>
    void AudioSystem::Shutdown() {
        CheckFMODResult(_system->release());
    }

    /// <summary>
    /// Updates the audio system state by processing pending audio operations.
    /// </summary>
    void AudioSystem::Update() {
        CheckFMODResult(_system->update());
    }

    /// <summary>
    /// Adds a sound to the audio system using the specified filename and name.
    /// </summary>
    /// <param name="filename">The path to the sound file to be loaded.</param>
    /// <param name="name">The name to associate with the sound. If empty, the filename is used as the key.</param>
    /// <returns>True if the sound was successfully added; false if the name already exists or loading failed.</returns>
    bool AudioSystem::AddSound(const std::string& filename, const std::string& name) {
        std::string key = (name.empty()) ? filename : name;
        key = tolower(key);

        // Check if key exists in sounds map
        if (_sounds.find(key) != _sounds.end()) {
            Logger::Warning("Audio System: Name Already Exists - {}", key);
            return false;
        }

        // Create sound from key
        FMOD::Sound* sound = nullptr;
        FMOD_RESULT result = _system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
        if (!CheckFMODResult(result)) return false;

        // Insert into map
        _sounds[key] = sound;

        return true;
    }

    ///
    bool AudioSystem::PlaySound(const std::string& name) {
        std::string key = name;
        key = tolower(key);

        // Check if sound exists
        if (_sounds.find(key) == _sounds.end()) {
            Logger::Warning("Audio System: Name Doesn't Exist - {}", key);
            return false;
        }

        // Play sound from key
        FMOD_RESULT result = _system->playSound(_sounds[key], 0, false, nullptr);
        if (!CheckFMODResult(result)) return false;

        return true;
    }

    bool AudioSystem::PlaySound(AudioClip& audioClip) {
        FMOD_RESULT result = _system->playSound(audioClip._sound, 0, false, nullptr);
        if (!CheckFMODResult(result)) return false;

        return true;
    }
}
