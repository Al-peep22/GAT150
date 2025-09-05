#pragma once

namespace viper {
	class Texture;
	class TextureAnimation : public Resource {
	public:
		TextureAnimation() = default;

		~TextureAnimation() = default;

		bool Load(const std::string& filename, class Renderer& renderer);

		vec2 GetSize() const;

		rect GetFrameRect(int frame) const;

		int GetTotalFrames() const { return _totalFrames; }

		float GetFPS() const { return _framesPerSecond; }

		bool IsValidFrame(int frame) const { return frame >= 0 && frame < _totalFrames; }

		bool IsLooping() const { return _loop; }

		res_t<Texture> GetTexture() { return _texture; }

	private:
		int _columns = 0; // The number of horizontal sub images in the image
		int _rows = 0; // The number of vertical sub images in the image
		int _startFrame = 0; // The start frame, frame = 0 is the first frame
		int _totalFrames = 0; // The number of frames in the animation

		float _framesPerSecond = 0; // Frames per second (usually 10-15 frames per second)

		bool _loop = true; // Whether the animations should loop

		res_t<Texture> _texture;
	};

}