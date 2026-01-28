#pragma once
#include <vector>
#include "Layer.h"
#include <Engine/GameObject.h>
#include <Engine/InputManager.h>
#include <Engine/SoundManager.h>
#include <Engine/Time.h>


namespace Engine {

	class Core {
	public:



		Core();
		virtual ~Core();


		virtual void run();

		void addLayer(Layer* layer);

	private:

		bool running{ true };
		std::vector<Layer*> layers;
	};
}