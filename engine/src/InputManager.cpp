#include <Engine/InputManager.h>

namespace Engine {


	InputManager::InputManager() {
		m_keyboardState = SDL_GetKeyboardState(nullptr);
	}

	void InputManager::Update() {
	}

	bool InputManager::GetKeyDown(SDL_Scancode scanCode) {

		return keyMap[scanCode];
	}

	bool InputManager::GetKeyPressed(SDL_Scancode scanCode)
	{

		bool pressed = keyMap[scanCode];
		keyMap[scanCode] = false;
		return pressed;
	}

	bool InputManager::GetKeyUp(SDL_Scancode scanCode) {

		bool pressed = keyMapUp[scanCode];
		keyMapUp[scanCode] = false;
		return pressed;

	}

}