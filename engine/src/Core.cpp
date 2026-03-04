#include "Engine/Core.h"
#include <iostream>
#include <Engine/WindowManager.h>
#include <Engine/Renderer.h>
#include <Engine/EventManager.h>
#include <chrono>
#include <Engine/PhysicsManager.h>
#include <Engine/CollisionManager.h>
#include <Engine/AnimationManager.h>

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

		Engine::AnimationManager& animationManager = Engine::AnimationManager::Get();


		Engine::PhysicsManager& physics = Engine::PhysicsManager::Get();

		// make sure SDL video & audio is init
		if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
			SDL_Log("SDL_Init Failed: %s", SDL_GetError());
		}
		// call start() for all layers
		if(m_scene != nullptr){
			m_scene->start();
		}

		const float fixedDeltaTime = 1.0f / 60.0f;

		auto lastTime = std::chrono::high_resolution_clock::now();

		double lag = 0.0f;
		while (m_running) {

			auto currentTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> frameTime = currentTime - lastTime;
			lastTime = currentTime;

			float deltaTime = frameTime.count();

			// Clamp deltaTime to avoid physics explosions
			if (deltaTime > 0.25)
				deltaTime = 0.25;

			lag += deltaTime;

			EventManager::Get().PollEvents(m_running);

			while (lag >= fixedDeltaTime) {
				Engine::Time::deltaTime = fixedDeltaTime;

				physics.update();

				if (m_scene != nullptr) {
					m_scene->update();
				}
				lag -= fixedDeltaTime;
			}

			animationManager.Update();
			renderer.draw();
			window.swapBuffers();
			Time::timeCount++;


		}


		window.DestroyWindow();


	}

	void Core::setScene(Scene* scene)
	{
		m_scene = scene;
	}

}
