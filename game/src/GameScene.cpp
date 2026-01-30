#include <Game/GameScene.h>
#include <iostream>


// this is the heart of the game
namespace Game {
	using namespace glm;

	Engine::GameObject player;



	void GameScene::start() {
		std::cout << "Hello World!\n";
		player.addComponent<Engine::Transform>();
		player.addComponent<Engine::Sprite>()->LoadSprite("Assets/HorribleBox64x64.png");
		

		Engine::SoundManager& sound = Engine::SoundManager::Get();
		//sound.PlaySound();
	}

	void GameScene::update() {
		Engine::Transform* transform = player.getComponent<Engine::Transform>();
		Engine::InputManager& input = Engine::InputManager::Get();
		if (input.GetKeyDown(SDL_SCANCODE_A)) {
			transform->translate(vec3(-10, 0, 0) * Engine::Time::deltaTime);
		}
		if (input.GetKeyDown(SDL_SCANCODE_D)) {
			transform->translate(vec3(10, 0, 0) * Engine::Time::deltaTime);
		}
		if (input.GetKeyDown(SDL_SCANCODE_W)) {
			transform->translate(vec3(0, 10, 0) * Engine::Time::deltaTime);
		}
		if (input.GetKeyDown(SDL_SCANCODE_S)) {
			transform->translate(vec3(0, -10, 0) * Engine::Time::deltaTime);
		}
		if (input.GetKeyDown(SDL_SCANCODE_SPACE)) {
			std::cout
				<< "( " << transform->position.x
				<< ", " << transform->position.y
				<< ", " << transform->position.z
				<< " )" << std::endl;
		}

	}
}