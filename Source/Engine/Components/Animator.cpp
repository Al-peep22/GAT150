#include "EnginePCH.h"
#include "Animator.h"
#include "Engine.h"

#include "SpriteRenderer.h"

namespace viper {
	FACTORY_REGISTER(Animator)

	void Animator::Start() {
		// Cash off sprite Renderer component, using sprite renderer to draw
		_spriteRenderer = owner->GetComponent<SpriteRenderer>();
		if (!_spriteRenderer) {
			Logger::Error("Animator missing sprite renderer.");
		}

		// Get texture animations from texture animation names
		for (auto& animation : _animations) {
			animation.second.textureAnimation = Resources().Get<TextureAnimation>(animation.second.textureAnimationName, GetEngine().GetRenderer());

			if (!animation.second.textureAnimation) {
				Logger::Warning("Could not load Animator texture animation: {}", animation.second.textureAnimationName);
			}
			else {
				Logger::Info("Animator animation {}, texture {} loaded", animation.first, animation.second.textureAnimationName);
			}
		}

		// Set initial animation, use first map entry
		auto it = _animations.begin();
		std::string name = it->first;
		Play(name);
	}

	void Animator::Update(float dt) {
		if (_paused || !_currentAnimation.textureAnimation) return;

		// Update frame timer
		_frameTimer -= dt * speedMultiplier;
		if (_frameTimer <= 0) {
			_frameTimer = 1.0f / _currentAnimation.textureAnimation->GetFPS();
			frame++;

			// Check if animation is complete, lopp on last frame
			if (frame >= _currentAnimation.textureAnimation->GetTotalFrames()) {
				if (_currentAnimation.textureAnimation->IsLooping()) {
					frame = 0;
				}
				else {
					frame = _currentAnimation.textureAnimation->GetTotalFrames() - 1;
				}
			}

			// Set texture rect from animation
			if (_spriteRenderer) {
				_spriteRenderer->textureRect = _currentAnimation.textureAnimation->GetFrameRect(frame);
			}
		}
	}

	void Animator::Play(const std::string& name, bool resetFrame) {
		// Don't start animation if it's already the current animation
		if (equalsIqnoreCase(name, _currentAnimationName)) return;

		// Check if animation exists
		auto it = _animations.find(tolower(name));
		if (it == _animations.end()) {
			Logger::Error("Animation does not exist in animation {}", name);
			return;
		}

		// Set the current animation 
		_currentAnimationName = name;
		_currentAnimation = it->second;

		if (resetFrame) frame = 0;
		_frameTimer = 1.0f / _currentAnimation.textureAnimation->GetFPS();

		// Set sprite renderer texture
		if (_spriteRenderer) {
			_spriteRenderer->texture = _currentAnimation.textureAnimation->GetTexture();
			_spriteRenderer->textureRect = _currentAnimation.textureAnimation->GetFrameRect(frame);
		}
	}

	void Animator::Read(const json::value_t& value) {
		Object::Read(value);

		JSON_READ(value, frame);

		if (JSON_HAS(value, animations) && JSON_GET(value, animations).IsArray()) {
			for (auto& animatorValue : JSON_GET(value, animations).GetArray()) {
				std::string name;
				std::string textureAnimationName;

				JSON_READ(animatorValue, name);

				JSON_READ_NAME(animatorValue, "texture_animation", textureAnimationName);

				TextureAnimInfo textureAnimInfo;
				textureAnimInfo.textureAnimationName = textureAnimationName;

				_animations[tolower(name)] = textureAnimInfo;
			}
		}
	}

}
