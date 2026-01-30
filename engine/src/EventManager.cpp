#include <Engine/EventManager.h>
#include <Engine/InputManager.h>
#include <SDL3/SDL.h>
namespace Engine {


	using namespace std;
	void EventManager::PollEvents(bool& running) {

		Engine::InputManager& input = Engine::InputManager::Get();

		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) {
				running = false;
			}

			if (e.type == SDL_EVENT_KEY_DOWN) {
				input.Update();
			}

			if (e.type == SDL_EVENT_KEY_UP) {
				input.Update();
			}

		}
	}
}