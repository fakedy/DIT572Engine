#include <Engine/EventManager.h>
#include <Engine/InputManager.h>
#include <SDL3/SDL.h>

namespace Engine {

	Engine::InputManager& input = Engine::InputManager::Get();

	void EventManager::PollEvents(bool& running) {

		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) {
				running = false;
			}

			if (e.type == SDL_EVENT_KEY_DOWN) {
				SDL_Log("Key pressed: %s", SDL_GetKeyName(e.key.key));
			}

		}
	}
}