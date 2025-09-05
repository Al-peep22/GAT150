#include "Renderer.h"
#include "Texture.h"

namespace viper {
    bool Renderer::Initialize() {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            Logger::Error("SDL_INIT ERROR: {}", SDL_GetError());
            return false;
        }

        if (!TTF_Init()) {
            Logger::Error("TTF_INIT ERROR: {}", SDL_GetError());
            return false;
        }

        return true;
    }

    void Renderer::Shutdown() {
        TTF_Quit();
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
        SDL_Quit();
    }

    bool Renderer::CreateWindow(const std::string& name, int width, int height, bool fullscreen) {
        _width = width;
        _height = height;

        _window = SDL_CreateWindow(name.c_str(), width, height, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
        if (_window == nullptr) {
            Logger::Error("SDL_CreateWindow Error: {}", SDL_GetError());
            SDL_Quit();
            return false;
        }

        _renderer = SDL_CreateRenderer(_window, NULL);
        if (_renderer == nullptr) {
            Logger::Error("SDL_CreateRenderer Error: {}", SDL_GetError());
            SDL_DestroyWindow(_window);
            SDL_Quit();
            return false;
        }

        SDL_SetRenderVSync(_renderer, 1);
        SDL_SetRenderLogicalPresentation(_renderer, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

        return true;
    }

    void Renderer::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	    SDL_SetRenderDrawColor(_renderer, r, g, b, a);
    }

    void Renderer::SetColor(float r, float g, float b, float a) {
        SDL_SetRenderDrawColorFloat(_renderer, r, g, b, a);
    }

    void Renderer::Clear() {
	    SDL_RenderClear(_renderer);
    }

    void Renderer::Present() {
	    SDL_RenderPresent(_renderer);
    }

    void Renderer::DrawLine(float x1, float y1, float x2, float y2) {
        SDL_RenderLine(_renderer, x1, y1, x2, y2);
    }
    void Renderer::DrawPoint(float x, float y) {
		SDL_RenderPoint(_renderer, x, y);
    }
    void Renderer::DrawTexture(Texture& texture, float x, float y) {
        vec2 size = texture.GetSize();

        SDL_FRect destRect;
        destRect.x = x;
        destRect.y = y;
        destRect.w = size.x;
        destRect.h = size.y;

        SDL_RenderTexture(_renderer, texture._texture, NULL, &destRect);
    }

    void Renderer::DrawTexture(Texture& texture, float x, float y, float angle, float scale, bool flipH) {
        vec2 size = texture.GetSize();

        SDL_FRect destRect;
        destRect.w = size.x * scale;
        destRect.h = size.y * scale;
        destRect.x = x - (destRect.w * 0.5f);
        destRect.y = y - (destRect.h * 0.5f);

        SDL_RenderTextureRotated(_renderer, texture._texture, NULL, &destRect, angle, NULL, (flipH ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE));
    }

    void Renderer::DrawTexture(Texture& texture, const rect& sourceRect, float x, float y, float angle, float scale, bool flipH) {
        // convert rect to SDL_FRect
        SDL_FRect srcRect;
        srcRect.x = sourceRect.x;
        srcRect.y = sourceRect.y;
        srcRect.w = sourceRect.w;
        srcRect.h = sourceRect.h;

        SDL_FRect destRect;
        destRect.w = srcRect.w * scale;
        destRect.h = srcRect.h * scale;
        destRect.x = x - destRect.w * 0.5f;
        destRect.y = y - destRect.h * 0.5f;

        SDL_RenderTextureRotated(_renderer, texture._texture, &srcRect, &destRect, angle, NULL, (flipH ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE));
    }
}
