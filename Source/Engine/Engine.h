#pragma once
#include "Audio/AudioSystem.h"
#include "Core/Singleton.h"
#include "Core/Time.h"
#include "Input/InputSystem.h"
#include "Physics/Physics.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Renderer.h"
#include "Resources/ResourceManager.h"

#include <memory>

namespace viper {
	class Engine : public Singleton<Engine> {
	public:
		bool Initialize();
		void Update();
		void Draw();
		void Shutdown();

		Renderer& GetRenderer() { return *_renderer; }
		InputSystem& GetInput() { return *_input; }
		AudioSystem& GetAudio() { return *_audio; }
		ParticleSystem& GetParticleSystem() { return *_particleSystem; }
		Physics& GetPhysics() { return *_physics; }

		Time& GetTime() { return _time; }

	private:
		friend class Singleton<Engine>;
		Engine() = default;

	private:
		Time _time;

		std::unique_ptr<AudioSystem> _audio;
		std::unique_ptr<InputSystem> _input;
		std::unique_ptr<Renderer> _renderer;
		std::unique_ptr<ParticleSystem> _particleSystem;
		std::unique_ptr<Physics> _physics;
	};

	inline Engine& GetEngine() { return Engine::Instance(); };
}