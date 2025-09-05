#include "Engine.h"

namespace viper {
	bool Engine::Initialize() {
		_renderer = std::make_unique<Renderer>();
		_renderer->Initialize();
		_renderer->CreateWindow("viper Engine", 1280, 1024, false);

		_input = std::make_unique<InputSystem>();
		_input->Initialize();

		_audio = std::make_unique<AudioSystem>();
		_audio->Initialize();

		_particleSystem = std::make_unique<ParticleSystem>();
		_particleSystem->Initialize(5000);

		_physics = std::make_unique<Physics>();
		_physics->Initialize();
		return true;
	}

	void Engine::Update() {
		_time.Tick();
		_input->Update();
		_audio->Update();
		_particleSystem->Update(_time.GetDeltaTime());
		_physics->Update(_time.GetDeltaTime());
	}

	void Engine::Draw() {
		//
	}

	void Engine::Shutdown()	{
		// Release resources from rescource manager
		Resources().RemoveAll();
		Factory::Instance().RemoveAll();
		EventManager::Instance().RemoveAll();

		// Shutdown engine systems
		_physics->Shutdown();
		_particleSystem->ShutDown();
		_audio->Shutdown();
		_input->Shutdown();
		_renderer->Shutdown();
	}
}

