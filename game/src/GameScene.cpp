#include <Game/GameScene.h>
#include <iostream>
#include <Game/World.h>

// this is the heart of the game
namespace Game {
	using namespace glm;

	Engine::GameObject player;

	Engine::GameObject box;

	void GameScene::start() {
		player.addComponent<Engine::Sprite>()->LoadSprite("Assets/cursed.png");

		box.addComponent<Engine::Sprite>()->LoadSprite("Assets/box.png");
		box.getComponent<Engine::Transform>()->translate(vec3(6, 0, 0));

		Engine::Renderer& renderer = Engine::Renderer::Get();
		renderer.pixels_per_unit = 16.0f;

		Engine::SoundManager& sound = Engine::SoundManager::Get();



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