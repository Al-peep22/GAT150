#pragma once
#include "Math/Vector2.h"
#include <vector>
#include <array>

namespace viper {
	class InputSystem {
	public:
		enum class MouseButton : uint8_t {
			LEFT,
			MIDDLE,
			RIGHT
		};

	public:
		InputSystem() = default;

		bool Initialize();

		void Shutdown();

		void Update();

		// KEYBOARD INPUT
		bool GetKeyDown(uint8_t key) const { return _keyboardState[key]; }
		bool GetPrevKeyDown(uint8_t key) const { return _prevKeyboardState[key]; }
		bool GetKeyPressed(uint8_t key) const { return !_prevKeyboardState[key] && _keyboardState[key]; }
		bool GetKeyReleased(uint8_t key) const { return _prevKeyboardState[key] && !_keyboardState[key]; }

		//MOUSE INPUT
		bool GetMouseButtonDown(MouseButton button) { return _mouseButtonState[static_cast<uint8_t>(button)]; }
		bool GetPrevMouseButtonDown(MouseButton button) { return _prevMouseButtonState[static_cast<uint8_t>(button)]; }
		bool GetMouseButtonPressed(MouseButton button) { return !_prevMouseButtonState[static_cast<uint8_t>(button)] && _mouseButtonState[static_cast<uint8_t>(button)]; }
		bool GetMouseButtonReleased(MouseButton button) { return _prevMouseButtonState[static_cast<uint8_t>(button)] && !_mouseButtonState[static_cast<uint8_t>(button)]; }

		const vec2& GetMousePosition() const { return _mousePosition; }
		const vec2& GetPrevMousePosition() const { return _PrevMousePosition; }

	private:
		std::vector<bool> _keyboardState;
		std::vector<bool> _prevKeyboardState;

		vec2 _mousePosition { 0, 0 };
		vec2 _PrevMousePosition { 0, 0 };

		std::array<bool, 3> _mouseButtonState{ false, false, false };
		std::array<bool, 3> _prevMouseButtonState{ false, false, false };
	};
}