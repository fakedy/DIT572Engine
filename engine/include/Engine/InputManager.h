#pragma once
#include <SDL3/SDL.h>

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

		bool GetKeyDown(SDL_Event e);


	private:
		const bool* _keyboardState;
	};
}