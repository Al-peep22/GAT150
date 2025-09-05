#include "Font.h"

namespace viper {
	/// <summary>
	/// Destroys the Font object and releases associated resources.
	/// </summary>
	Font::~Font() {
		if (_ttfFont != nullptr) {
			TTF_CloseFont(_ttfFont);
		}
	}

	/// <summary>
	/// Loads a font from the specified file with the given size.
	/// </summary>
	/// <param name="name">The path to the font file to load.</param>
	/// <param name="fontSize">The desired size of the font.</param>
	/// <returns>True if the font was loaded successfully; false otherwise.</returns>
	bool Font::Load(const std::string& name, float fontSize) {
		_ttfFont = TTF_OpenFont(name.c_str(), fontSize);
		if (_ttfFont == nullptr) {
			Logger::Error("Could not load font: {}", name);
			return false;
		}

		return true;
	}
}

