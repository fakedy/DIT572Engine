#include "Engine/Core.h"
#include <iostream>
#include <Engine/WindowManager.h>
#include <Engine/Renderer.h>
#include <Engine/EventManager.h>
#include <chrono>
#include <Engine/PhysicsManager.h>

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

		Engine::PhysicsManager& physics = Engine::PhysicsManager::Get();

		// make sure SDL video & audio is init
		if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
			SDL_Log("SDL_Init Failed: %s", SDL_GetError());
		}
		// call start() for all layers
		if(_scene != nullptr){
			_scene->start();
		}

		auto lastTime = std::chrono::high_resolution_clock::now();

		while (running) {

			auto currentTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> frameTime = currentTime - lastTime;

			Time::deltaTime = frameTime.count();

			physics.update();

			EventManager::Get().PollEvents(running);

			if (_scene != nullptr) {
				_scene->update();
			}

			renderer.clear();
			renderer.draw();
			window.swapBuffers();

			lastTime = currentTime;

		}


		window.DestroyWindow();


	}

	void Core::setScene(Scene* scene)
	{
		_scene = scene;
	}

}
