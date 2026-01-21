#include "Engine/Core.h"
#include <iostream>
#include <Engine/WindowManager.h>
#include <Engine/Renderer.h>
#include <Engine/InputManager.h>

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
		Engine::InputManager& input = Engine::InputManager::Get();


		for (Layer* layer : layers) {
			layer->start();
		}

		while (running) {

			for (Layer* layer : layers) {
				layer->update();
			}

			input.Update();

			renderer.clear();

			window.swapBuffers();


		}


		window.DestroyWindow();


	}

	void Core::addLayer(Layer* layer)
	{
		layers.push_back(layer);
	}
}
