#pragma once
#include <SDL3/SDL.h>
#include <unordered_map>

namespace Engine {

	class InputManager {
	public:
		// singleton
		static InputManager& Get() {
			static InputManager instance;
			return instance;
		}
		InputManager();

		~InputManager() = default;

		void Update();

		bool GetKeyPressed(SDL_Scancode scanCode);

		bool GetKeyDown(SDL_Scancode scanCode);


		std::unordered_map<uint32_t, bool> keyMap;
	private:
		const bool* _keyboardState;
	};
}