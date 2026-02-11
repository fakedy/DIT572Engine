#include <Game/GameScene.h>
#include <iostream>
#include <Game/World.h>

// this is the heart of the game
namespace Game {
	using namespace glm;

	Engine::GameObject player;

	Engine::GameObject box;
	World world;

	Engine::GameObject floor;
	
	void GameScene::start() {
		Engine::Renderer& renderer = Engine::Renderer::Get();
		renderer.pixels_per_unit = 16.0f;


		player.addComponent<Engine::Sprite>()->LoadSprite("Assets/cursed.png");
		float playerSizeX = player.getComponent<Engine::Sprite>()->material->texture->width;
		float playerSizeY = player.getComponent<Engine::Sprite>()->material->texture->height;
		player.addComponent<Engine::BoxCollider2D>()->width = playerSizeX / renderer.pixels_per_unit;
		player.getComponent<Engine::BoxCollider2D>()->height = playerSizeY / renderer.pixels_per_unit;
		player.addComponent<Engine::RigidBody2D>();

		player.getComponent<Engine::Transform>()->scale(vec3(-1, 1, 1));


		box.addComponent<Engine::Sprite>()->LoadSprite("Assets/box.png");
		box.getComponent<Engine::Transform>()->translate(vec3(6, 0, 0));
		box.addComponent<Engine::RigidBody2D>();

		float boxSizeX = box.getComponent<Engine::Sprite>()->material->texture->width;
		float boxSizeY = box.getComponent<Engine::Sprite>()->material->texture->height;
		box.addComponent<Engine::BoxCollider2D>()->width = boxSizeX / renderer.pixels_per_unit;
		box.getComponent<Engine::BoxCollider2D>()->height = boxSizeY / renderer.pixels_per_unit;
		box.addComponent<Engine::RigidBody2D>();


		floor.addComponent<Engine::Sprite>()->LoadSprite("Assets/stone.png");
		float floorSizeX = floor.getComponent<Engine::Sprite>()->material->texture->width;
		float floorSizeY = floor.getComponent<Engine::Sprite>()->material->texture->height;
		floor.getComponent<Engine::Transform>()->scale(vec3(100, 1, 1));
		floor.addComponent<Engine::BoxCollider2D>()->width = 100;
		floor.getComponent<Engine::BoxCollider2D>()->height = floorSizeY / renderer.pixels_per_unit;
		floor.getComponent<Engine::BoxCollider2D>()->isStatic = true;
		floor.getComponent<Engine::Transform>()->translate(vec3(0, -10, 0));



		Engine::SoundManager& sound = Engine::SoundManager::Get();
		
	}

	void GameScene::update() {
		Engine::Transform* transform = player.getComponent<Engine::Transform>();
		Engine::InputManager& input = Engine::InputManager::Get();
		if (input.GetKeyPressed(SDL_SCANCODE_A)) {
			transform->translate(vec3(-10, 0, 0) * Engine::Time::deltaTime);
			transform->scale(vec3(-1, 1, 1));
		}
		if (input.GetKeyPressed(SDL_SCANCODE_D)) {
			transform->translate(vec3(10, 0, 0) * Engine::Time::deltaTime);
			transform->scale(vec3(1, 1, 1));
		}
		if (input.GetKeyPressed(SDL_SCANCODE_W)) {
			transform->translate(vec3(0, 20, 0) * Engine::Time::deltaTime);
		}
		if (input.GetKeyPressed(SDL_SCANCODE_S)) {
			transform->translate(vec3(0, -10, 0) * Engine::Time::deltaTime);
		}
		if (input.GetKeyDown(SDL_SCANCODE_SPACE)) {
			player.getComponent<Engine::RigidBody2D>()->addForce(glm::vec3(0, 2000.0f, 0));
		}

	}
}