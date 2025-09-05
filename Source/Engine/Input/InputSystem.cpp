#include "InputSystem.h"

bool viper::InputSystem::Initialize()
{
	//Keyboard INIT
	int numKeys;

	const bool* keyboardState = SDL_GetKeyboardState(&numKeys);
	
	_keyboardState.resize(numKeys);
	std::copy(keyboardState, keyboardState + numKeys, _keyboardState.begin());
	_prevKeyboardState = _keyboardState;

	//Mouse INIT
	SDL_GetMouseState(&_mousePosition.x, &_mousePosition.y);
	_PrevMousePosition = _mousePosition;

	return true;
}

void viper::InputSystem::Shutdown()
{
	//
}

void viper::InputSystem::Update()
{
	//Keyboard Input
	_prevKeyboardState = _keyboardState;
	const bool* keyboardState = SDL_GetKeyboardState(nullptr);
	std::copy(keyboardState, keyboardState + _keyboardState.size(), _keyboardState.begin());

	//Mouse Input
	_PrevMousePosition = _mousePosition;

	_prevMouseButtonState = _mouseButtonState;
	uint32_t mouseButtonState = SDL_GetMouseState(&_mousePosition.x, &_mousePosition.y);

	_mouseButtonState[static_cast<uint8_t>(MouseButton::LEFT)] = mouseButtonState & SDL_BUTTON_LMASK;
	_mouseButtonState[static_cast<uint8_t>(MouseButton::MIDDLE)] = mouseButtonState & SDL_BUTTON_MMASK;
	_mouseButtonState[static_cast<uint8_t>(MouseButton::RIGHT)] = mouseButtonState & SDL_BUTTON_RMASK;

}