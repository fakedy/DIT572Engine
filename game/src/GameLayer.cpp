#include <Game/GameLayer.h>
#include <iostream>


// this is the heart of the game
namespace Game {
	using namespace glm;

	Engine::GameObject player;




	void GameLayer::start() {
		std::cout << "Hello World!\n";
		player.addComponent<Engine::Transform>(); 
		player.addComponent<Engine::Sprite>();

		Engine::SoundManager& sound = Engine::SoundManager::Get();
		//sound.PlaySound();
	}

	void GameLayer::update() {
		Engine::Transform* transform = player.getComponent<Engine::Transform>();
		Engine::InputManager& input = Engine::InputManager::Get();
		if (input.GetKeyDown(SDL_SCANCODE_A)) {
			transform->translate(vec3(-100, 0, 0) * Engine::Time::deltaTime );
		}
		if (input.GetKeyDown(SDL_SCANCODE_D)) {
			transform->translate(vec3(100, 0, 0) * Engine::Time::deltaTime);
		}

		/*
		std::cout
			<< "( " << transform->position.x
			<< ", " << transform->position.y
			<< ", " << transform->position.z
			<< " )" << std::endl;
		*/
	}
}