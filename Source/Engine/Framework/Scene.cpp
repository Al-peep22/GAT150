#include "Scene.h"
#include "Actor.h"
#include "Components/ColliderComponent.h"
#include "Renderer/Renderer.h"

namespace viper {
	/// <summary>
	/// Updates the scene by processing actor updates, removing destroyed actors, and handling collisions between actors.
	/// </summary>
	/// <param name="dt">The time delta in seconds since the last update.</param>
	void Scene::Update(float dt) {
		// Update all actors
		for (auto& actor : _actors) {
			if (actor->active) {
				actor->Update(dt);
			}
		}

		// Remove destroyed actors
		/*std::erase_if(_actors, [](Actor actor) {
			return (actor->destroyed);
		});*/

		for (auto iter = _actors.begin(); iter != _actors.end();) {
			if ((*iter)->destroyed) {
				iter = _actors.erase(iter);
			}
			else {
				iter++;
			}
		}

		// Check for collisions
		//for (auto& actorA : _actors) {
		//	for (auto& actorB : _actors) {
		//		continue;

		//		if (actorA == actorB || (actorA->destroyed || actorB->destroyed)) continue;

		//		auto colliderA = actorA->GetComponent<ColliderComponent>();
		//		auto colliderB = actorB->GetComponent<ColliderComponent>();

		//		// Make sure both actors have a collider
		//		if (!colliderA || !colliderB) continue;

		//		if (colliderA->CheckCollision(*colliderB)) {
		//			actorA->OnCollision(actorB.get());
		//			actorB->OnCollision(actorA.get());
		//		}
		//	}
		//}
	}

	/// <summary>
	/// Draws all active actors in the scene using the specified renderer.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the actors.</param>
	void Scene::Draw(Renderer& renderer) {
		for (auto& actor : _actors) {
			if (actor->active) {
				actor->Draw(renderer);
			}
		}
	}

	/// <summary>
	/// Adds an actor to the scene, transferring ownership of the actor to the scene.
	/// </summary>
	/// <param name="actor">A unique pointer to the actor to be added to the scene.</param>
	void Scene::AddActor(std::unique_ptr<class Actor> actor, bool start) {
		actor->scene = this;
		if (start) actor->Start();
		_actors.push_back(std::move(actor));
	}

	/// <summary>
	/// Removes all actors from the scene.
	/// </summary>
	void Scene::RemoveAllActors(bool force) {
		for (auto iter = _actors.begin(); iter != _actors.end();) {
			if (!(*iter)->persistent || force) {
				iter = _actors.erase(iter);
			}
			else {
				iter++;
			}
		}
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="sceneName"></param>
	/// <returns></returns>
	bool Scene::Load(const std::string& sceneName) {
		// Load json
		json::document_t document;
		if (!json::Load(sceneName, document)) {
			Logger::Error("Could not load scene {}", sceneName);
			return false;
		}

		// Create scene
		Read(document);

		// Start actors
		for (auto& actor : _actors) {
			actor->Start();
		}

		return true;
	}

	void Scene::Read(const json::value_t& value) {
		// Read prototype actor
		if (JSON_HAS(value, prototypes)) {
			for (auto& prototypeValue : JSON_GET(value, prototypes).GetArray()) {
				auto actor = Factory::Instance().Create<Actor>("Actor");
				actor->Read(prototypeValue);

				std::string name = actor->name;

				Factory::Instance().RegisterPrototype<Actor>(name, std::move(actor));
			}
		}

		// Read actor
		if (JSON_HAS(value, actors)) {
			for (auto& actorValue : JSON_GET(value, actors).GetArray()) {
				auto actor = Factory::Instance().Create<Actor>("Actor");
				actor->Read(actorValue);

				AddActor(std::move(actor), false);
			}
		}
	}
}