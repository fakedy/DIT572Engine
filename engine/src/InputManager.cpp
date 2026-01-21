#include <engine/InputManager.h>

namespace Engine {


	InputManager::InputManager() {
		_keyboardState = SDL_GetKeyboardState(NULL);
	}

	void InputManager::Update() {
		// update keyboard state
		SDL_PumpEvents();
		_keyboardState = SDL_GetKeyboardState(NULL);
	}

	bool InputManager::GetKeyDown(SDL_Scancode key) {
		return _keyboardState[key];
	}


}