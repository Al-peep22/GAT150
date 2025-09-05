#include "TextureAnimation.h"

namespace viper {
	bool TextureAnimation::Load(const std::string& filename, class Renderer& renderer) {
		// Load json
		json::document_t document;
		if (!json::Load(filename, document)) {
			Logger::Error("Could not load TextureAnimation json: {}", filename);
			return false;
		}

		// Read texture name
		std::string texture_name;
		JSON_READ(document, texture_name);

		// Load texture
		_texture = Resources().Get<Texture>(texture_name, renderer);
		if (!_texture) {
			Logger::Error("Could not load texture in Texture Animation: {}", texture_name);
		}

		JSON_READ_NAME(document, "columns", _columns);
		JSON_READ_NAME(document, "rows", _rows);
		JSON_READ_NAME(document, "start_frame", _startFrame);
		JSON_READ_NAME(document, "total_frames", _totalFrames);
		JSON_READ_NAME(document, "frames_per_second", _framesPerSecond);
		JSON_READ_NAME(document, "loop", _loop);

		return true;
	}

	vec2 TextureAnimation::GetSize() const {
		vec2 size = _texture->GetSize();

		return { size.x / _columns, size.y / _rows };
	}

	rect TextureAnimation::GetFrameRect(int frame) const {
		if (!IsValidFrame(frame)) {
			Logger::Warning("Frame is outside bounds {}/{}", frame, _totalFrames);
			frame = 0;
		}

		rect frameRect;
		vec2 size = GetSize();

		frameRect.w = size.x;
		frameRect.h = size.y;
		frameRect.x = ((_startFrame + frame) % _columns) * frameRect.w;
		frameRect.y = ((_startFrame + frame) / _columns) * frameRect.h;

		return frameRect;
	
	}
}