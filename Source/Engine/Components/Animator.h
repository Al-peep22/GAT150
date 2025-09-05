#pragma once

#include "Framework/Component.h"
#include "Renderer/TextureAnimation.h"

namespace viper {
	class Animator : public Component {
	public:
		struct TextureAnimInfo {
			std::string textureAnimationName;
			res_t<TextureAnimation> textureAnimation;
		};

		int frame = 0;
		float speedMultiplier{ 1 };

	public:
		CLASS_PROTOTYPE(Animator)

		void Start() override;

		void Update(float dt) override;

		void Play(const std::string& name, bool resetFrame = true);
		void Pause(bool pause) { _paused = pause; }
		bool IsPaused() const { return _paused; }

		const std::string& GetCurrentAnimationName() const { return _currentAnimationName; }

		void Read(const json::value_t& value) override;

	private:
		float _frameTimer = 0;
		bool _paused = false;

		std::string _currentAnimationName;
		TextureAnimInfo _currentAnimation;

		std::map<std::string, TextureAnimInfo> _animations;
		class SpriteRenderer* _spriteRenderer{ nullptr };
	};
}