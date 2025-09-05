#include "Texture.h"
#include "Renderer.h"

namespace viper {
	Texture::~Texture() {
		if (!_texture) SDL_DestroyTexture(_texture);
	}

	bool Texture::Load(const std::string& filename, Renderer& renderer) {
		SDL_Surface* surface = IMG_Load(filename.c_str());

		if (!surface) {
			Logger::Info("Renderer/Texture.cpp Line 14");
			Logger::Error("Could not load image: {}", filename);
			return false;
		}

		_texture = SDL_CreateTextureFromSurface(renderer._renderer, surface);

		SDL_DestroySurface(surface);

		if (!_texture) {
			Logger::Error("Could not create texture: {}", filename);
			return false;
		}

	 	return true;
	}

	vec2 Texture::GetSize() {
		float w, h;
		SDL_GetTextureSize(_texture, &w, &h);
		return vec2{ w, h };
	}

}

