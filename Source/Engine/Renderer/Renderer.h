#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

#include "Texture.h"

namespace viper {
	class Renderer {
	public:
		Renderer() = default;

		bool Initialize();

		void Shutdown();

		bool CreateWindow(const std::string& name, int width, int height, bool fullscreen = false);

		void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

		void SetColor(float r, float g, float b, float a = 1.0f);

		void Clear();

		void Present();

		void DrawLine(float x1, float y1, float x2, float y2);

		void DrawPoint(float x, float y);

		void DrawTexture(Texture& texture, float x, float y);

		void DrawTexture(Texture& texture, float x, float y, float angle, float scale = 1.0f, bool flipH = false);

		void DrawTexture(class Texture& texture, const rect& sourceRect, float x, float y, float angle, float scale = 1, bool flipH = false);

		int GetWidth() const { return _width; }
		int GetHeight() const { return _height; }

	private:
		SDL_Window* _window = nullptr;
		SDL_Renderer* _renderer = nullptr;

		int _width{ 0 };
		int _height{ 0 };

		friend class Text;
		friend class Texture;
	};
}
