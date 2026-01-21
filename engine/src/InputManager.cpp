#include <engine/InputManager.h>

namespace Engine {


	InputManager::InputManager() {
		_keyboardState = SDL_GetKeyboardState(nullptr);
	}

	void InputManager::Update() {
		// update keyboard state
		_keyboardState = SDL_GetKeyboardState(nullptr);
	}

	bool InputManager::GetKeyDown(SDL_Scancode e) {
		return _keyboardState[e];
	}

}