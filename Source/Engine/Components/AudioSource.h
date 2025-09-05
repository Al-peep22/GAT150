#pragma once

#include "Framework/Component.h"

namespace viper {
	class AudioSource : public Component {
	public:
		std::string audioClipName;

	public:
		CLASS_PROTOTYPE(AudioSource)

		void Update(float dt) override;
		void Play();
		void Read(const json::value_t& value) override;
	};
}