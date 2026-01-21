#include "Engine/Core.h"
#include <iostream>
#include <Engine/WindowManager.h>
#include <Engine/Renderer.h>
#include <Engine/InputManager.h>
#include <Engine/EventManager.h>

namespace Engine {

	Core::Core()
	{
	}

	Core::~Core()
	{
	}

	void Core::run()
	{

		Engine::WindowManager& window = Engine::WindowManager::Get();
		window.CreateWindow();
		Engine::Renderer& renderer = Engine::Renderer::Get();
		renderer.init();

		// make sure SDL video & audio is init
		if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
			SDL_Log("SDL_Init Failed: %s", SDL_GetError());
		}


		for (Layer* layer : layers) {
			layer->start();
		}

		while (running) {

			EventManager::Get().PollEvents(running);

			for (Layer* layer : layers) {
				layer->update();
			}

			renderer.clear();
			renderer.draw();
			window.swapBuffers();


		}


		window.DestroyWindow();


	}

	void Core::addLayer(Layer* layer)
	{
		layers.push_back(layer);
	}
}
