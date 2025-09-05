#include "AudioClip.h"

#include "AudioSystem.h"

namespace viper {
	/// <summary>
	/// Destroys the AudioClip object and releases associated sound resources.
	/// </summary>
	AudioClip::~AudioClip() {
		if (_sound) _sound->release();
	}

	/// <summary>
	/// Loads an audio clip from a file using the specified audio system.
	/// </summary>
	/// <param name="filename">The path to the audio file to load.</param>
	/// <param name="audioSystem">The audio system used to create and manage the sound.</param>
	/// <returns>True if the audio clip was loaded successfully; otherwise, false.</returns>
	bool AudioClip::Load(const std::string& filename, AudioSystem& audioSystem) {
		FMOD_RESULT result = audioSystem._system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &_sound);
		if (!AudioSystem::CheckFMODResult(result)) return false;

		return true;
	}

}