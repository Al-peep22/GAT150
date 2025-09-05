#pragma once
#include "Core/StringHelper.h"

#include "Core/Serializable.h"

#include <list>
#include <memory>
#include <string>
#include <vector>

namespace viper {
	class Actor;
	class Game;

	class Scene : public ISerializable {
	public:
		Scene(Game* game) : _game{ game } {};

		bool Load(const std::string& sceneName);

		void Read(const json::value_t& value) override;

		void Update(float dt);
		void Draw(class Renderer& renderer);

		void AddActor(std::unique_ptr<Actor>, bool start = true);

		void RemoveAllActors(bool force = false);

		template<typename T = Actor>
		T* GetActorByName(const std::string& name);

		template<typename T = Actor>
		std::vector<T*> GetActorsByTag(const std::string& tag);

		Game* GetGame() { return _game; }
		
	private:
		Game* _game{ nullptr };
		std::list < std::unique_ptr <Actor>> _actors;
		
	};

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="name"></param>
	/// <returns></returns>
	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name) {
		for (auto& actor : _actors) {
			if (viper::tolower(actor->name) == viper::tolower(name)) {
				T* object = dynamic_cast<T*>(actor.get());
				if (object) {
					return object;
				}
			}
		}
		return nullptr;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="tag"></param>
	/// <returns></returns>
	template<typename T>
	inline std::vector<T*> Scene::GetActorsByTag(const std::string& tag) {
		std::vector<T*> results;
		for (auto& actor : _actors) {
			if (tolower(actor->tag) == tolower(tag)) {
				T* object = dynamic_cast<T*>(actor.get());
				if (object) {
					results.push_back(object);
				}
			}
		}

		return results;
	}
}