#pragma once
#include "Core/Logger.h"
#include "Core/Singleton.h"
#include "Core/StringHelper.h"
#include "Resource.h"

#include <map>
#include <iostream>

namespace viper {
	class ResourceManager : public Singleton<ResourceManager> {
	public:
		template<typename T, typename ... Args>
		requires std::derived_from<T, Resource>
		res_t<T> Get(const std::string& filename, Args&& ... args);

		template<typename T, typename ... Args>
		requires std::derived_from<T, Resource>
		res_t<T> GetWithID(const std::string& id, const std::string& filename, Args&& ... args);

		void RemoveAll() { _resources.clear(); }

	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;

	private:
		std::map<std::string, res_t<Resource>> _resources;

	};

	template<typename T, typename ... Args>
	requires std::derived_from<T, Resource>
	inline res_t<T> ResourceManager::Get(const std::string& filename, Args&& ... args) {
		return GetWithID<T>(filename, filename, std::forward<Args>(args)...);
	}

	template<typename T, typename ...Args>
	requires std::derived_from<T, Resource>
	inline res_t<T> ResourceManager::GetWithID(const std::string& id, const std::string& filename, Args && ...args) {
		std::string key = tolower(id);

		auto iter = _resources.find(key);
		// Check if exits
		if (iter != _resources.end()) {
			// Get value in iterator
			auto base = iter->second;
			// Cast to data type T
			auto resource = std::dynamic_pointer_cast<T>(base);

			// Check if case was successful
			if (!resource) {
				Logger::Error("Resource type mismatch: {}", key);
				return res_t<T>();
			}

			// Return resource
			return resource;
		}

		// Load resource
		res_t<T> resource = std::make_shared<T>();
		if (resource->Load(filename, std::forward<Args>(args)...) == false) {
			Logger::Info("RESOURCES/RESOURCEMANAGER.H LINE 65");
			Logger::Error("Could not load resource: {}", filename);
			return res_t<T>();
		}

		// Add key to resource manager
		_resources[key] = resource;

		return resource;
	}

	inline ResourceManager& Resources() { return ResourceManager::Instance(); }
}