#include "Engine/Core.h"
#include <iostream>
#include <Engine/WindowManager.h>
#include <Engine/Renderer.h>
#include <Engine/EventManager.h>
#include <chrono>
#include <Engine/PhysicsManager.h>
#include <Engine/CollisionManager.h>

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

			// Clamp deltaTime to avoid physics explosions
			const float maxDelta = 0.05f; // 50 ms (20 FPS worst case)
			if (Time::deltaTime > maxDelta)
				Time::deltaTime = maxDelta;

			physics.update();

			EventManager::Get().PollEvents(running);

			if (_scene != nullptr) {
				_scene->update();
			}

			renderer.draw();
			window.swapBuffers();
			Time::timeCount++;

			lastTime = currentTime;

		}


		window.DestroyWindow();


	}

	void Core::setScene(Scene* scene)
	{
		_scene = scene;
	}

}
