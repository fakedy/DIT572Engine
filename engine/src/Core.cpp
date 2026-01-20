#include "Engine/Core.h"
#include <iostream>
#include <Engine/WindowManager.h>
#include <Engine/Renderer.h>

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


		for (Layer* layer : layers) {
			layer->start();
		}

		while (running) {

			for (Layer* layer : layers) {
				layer->update();
			}

			renderer.clear();

			window.swapBuffers();
		}


	}

	void Core::addLayer(Layer* layer)
	{
		layers.push_back(layer);
	}
}
