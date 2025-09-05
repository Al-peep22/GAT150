#include "TilemapRenderer.h"
#include "Renderer/Tilemap.h"
#include "Engine.h"

namespace viper {
	FACTORY_REGISTER(TilemapRenderer)

	TilemapRenderer::TilemapRenderer(const TilemapRenderer& other) {
	}

	void TilemapRenderer::Start() {
		// Load the tilemap resource
		_tilemap = Resources().Get<Tilemap>(_tilemapName, GetEngine().GetRenderer());
		if (!_tilemap) {
			Logger::Error("Could not load tilemap: {}", _tilemapName);
			return;
		}
		
		// create physics bodies
		Transform transform;
		transform.scale = owner->transform.scale;
		transform.rotation = owner->transform.rotation;

		PhysicsBody::PhysicsBodyDef bodyDef;
		bodyDef.isDynamic = false;
		bodyDef.actor = owner;

		// iterate through layers
		for (auto layer : _tilemap->GetLayers()) {

			if (!layer.hasCollision) continue;

			// get layer data (layout)
			for (int i = 0; i < layer.data.size(); i++) {
				int tileId = layer.data[i];
				if (tileId == 0) continue;

				rect source = _tilemap->GetTextureRect(layer, tileId);
				vec2 position = owner->transform.position + (_tilemap->GetPosition(layer, i) * owner->transform.scale);

				transform.position = position;
				vec2 size = vec2{ source.w, source.h };

				auto physicsBody = std::make_unique<PhysicsBody>(transform, size, bodyDef, GetEngine().GetPhysics());
				_physicsBodies.push_back(std::move(physicsBody));
			}
		}
	}

	void TilemapRenderer::Update(float dt) {
		//
	}

	void TilemapRenderer::Draw(Renderer& renderer) {
		// iterate through layers
		for (auto layer : _tilemap->GetLayers()) {
			// get layer data (layout)
			for (int i = 0; i < layer.data.size(); i++) {
				int tileId = layer.data[i];
				if (tileId == 0) continue;

				rect source = _tilemap->GetTextureRect(layer, tileId);
				vec2 position = owner->transform.position + _tilemap->GetPosition(layer, i) * owner->transform.scale;

				renderer.DrawTexture(*layer.texture, source, position.x, position.y, owner->transform.rotation, owner->transform.scale);
			}
		}
	}

	void TilemapRenderer::Read(const json::value_t& value) {
		Object::Read(value);

		JSON_READ_NAME(value, "tilemap_name", _tilemapName);
	}
}