#include "Text.h"

namespace viper {
	/// <summary>
	/// Destroys the Text object and releases its associated SDL texture if it exists.
	/// </summary>
	viper::Text::~Text() {
		if (_texture != nullptr) {
			SDL_DestroyTexture(_texture);
		}
	}

	/// <summary>
	/// Creates a text texture using the specified renderer, text string, and color.
	/// </summary>
	/// <param name="renderer">Reference to the Renderer object used for rendering the texture.</param>
	/// <param name="text">The string to be rendered as text.</param>
	/// <param name="color">The color of the text, represented as a vec3 (RGB components).</param>
	/// <returns>Returns true if the text texture was successfully created; otherwise, returns false.</returns>
	bool viper::Text::Create(Renderer& renderer, const std::string& text, const vec3& color) {
		// create a surface using the font, text string and color
		SDL_Color c{ (uint8_t)(color.r * 255), (uint8_t)(color.g * 255), (uint8_t)(color.b * 255), 255 };
		SDL_Surface* surface = TTF_RenderText_Solid(_font->_ttfFont, text.c_str(), text.size(), c);
		if (surface == nullptr) {
			Logger::Error("Could not create surface");
			return false;
		}

		// create a texture from the surface, only textures can render to the renderer
		_texture = SDL_CreateTextureFromSurface(renderer._renderer, surface);
		if (_texture == nullptr) {
			SDL_DestroySurface(surface);
			Logger::Error("Could not create texture: {}", SDL_GetError());
			return false;
		}

		// free the surface, no longer needed after creating the texture
		SDL_DestroySurface(surface);

		return true;
	}

	/// <summary>
	/// Draws the text texture at the specified position using the given renderer.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the text.</param>
	/// <param name="x">The x-coordinate where the text will be drawn.</param>
	/// <param name="y">The y-coordinate where the text will be drawn.</param>
	void viper::Text::Draw(Renderer& renderer, float x, float y) {
		// get the texture width and height
		float width, height;
		bool success = SDL_GetTextureSize(_texture, &width, &height);
		assert(success);

		// set the texture into the renderer at rect 
		SDL_FRect rect{ x, y, width, height };
		success = SDL_RenderTexture(renderer._renderer, _texture, NULL, &rect);
		assert(success);
	}
}

