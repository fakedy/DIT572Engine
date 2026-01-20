#include "Engine/Core.h"
#include <iostream>

namespace Engine {

	Core::Core()
	{
	}

	Core::~Core()
	{
	}

	void Core::run()
	{
		for (Layer* layer : layers) {
			layer->start();
		}

		while (running) {

			for (Layer* layer : layers) {

				layer->update();

			}
		}


	}

	void Core::addLayer(Layer* layer)
	{
		layers.push_back(layer);
	}
}
