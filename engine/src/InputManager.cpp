#include <engine/InputManager.h>

namespace Engine {


	InputManager::InputManager() {
		_keyboardState = SDL_GetKeyboardState(nullptr);
	}

	void InputManager::Update() {
		// update keyboard state
		_keyboardState = SDL_GetKeyboardState(nullptr);
	}

	bool InputManager::GetKeyDown(SDL_Event e) {
		SDL_Log("Key pressed: %s", SDL_GetKeyName(e.key.key));
		return _keyboardState[e.key.key];
	}

}