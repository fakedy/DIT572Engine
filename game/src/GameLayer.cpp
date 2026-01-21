#include <Game/GameLayer.h>
#include <Engine/GameObject.h>
#include <Engine/InputManager.h>
#include <Engine/SoundManager.h>
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
		if (input.GetKeyDown(SDL_SCANCODE_W)) {
			transform->translate(vec3(0, 0, 1));
		}

		if (input.GetKeyDown(SDL_SCANCODE_S)) {
			transform->translate(vec3(0, 0, -1));
		}
		if (input.GetKeyDown(SDL_SCANCODE_A)) {
			transform->translate(vec3(-1, 0, 0));
		}
		if (input.GetKeyDown(SDL_SCANCODE_D)) {
			transform->translate(vec3(1, 0, 0));
		}


		std::cout << "( " << transform->position.x
			<< ", " << transform->position.y
			<< ", " << transform->position.z
			<< " )" << std::endl;

	}
}