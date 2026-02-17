#include <Game/GameScene.h>
#include <iostream>
#include <Game/World.h>

// this is the heart of the game
namespace Game {
	using namespace glm;

	Engine::GameObject player;

	Engine::GameObject box;
	Engine::GameObject box2;
	Engine::GameObject box3;


	World world;

	Engine::GameObject floor;
	Engine::GameObject stoneGround;

	Engine::GameObject camera;
	
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
		player.getComponent<Engine::Transform>()->translate(vec3(0, 0, 5));


		box.addComponent<Engine::Sprite>()->LoadSprite("Assets/box.png");
		box.getComponent<Engine::Transform>()->translate(vec3(6, 0, 0));
		box.addComponent<Engine::RigidBody2D>();

		float boxSizeX = box.getComponent<Engine::Sprite>()->material->texture->width;
		float boxSizeY = box.getComponent<Engine::Sprite>()->material->texture->height;
		box.addComponent<Engine::BoxCollider2D>()->width = boxSizeX / renderer.pixels_per_unit;
		box.getComponent<Engine::BoxCollider2D>()->height = boxSizeY / renderer.pixels_per_unit;
		box.getComponent<Engine::BoxCollider2D>()->friction = 0.5f;
		box.addComponent<Engine::RigidBody2D>();

		box2.addComponent<Engine::Sprite>()->LoadSprite("Assets/box.png");
		box2.getComponent<Engine::Transform>()->translate(vec3(3, -8.5, 6));

		box3.addComponent<Engine::Sprite>()->LoadSprite("Assets/box.png");
		box3.getComponent<Engine::Transform>()->translate(vec3(-3, -8.5, 4));



		floor.addComponent<Engine::Sprite>()->LoadSprite("Assets/grass_stone.png");
		floor.getComponent<Engine::Sprite>()->getMaterial().samplerMode = Engine::Material::SAMPLER_MODE_REPEAT;
		float floorSizeX = floor.getComponent<Engine::Sprite>()->material->texture->width;
		float floorSizeY = floor.getComponent<Engine::Sprite>()->material->texture->height;
		floor.getComponent<Engine::Transform>()->scale(vec3(100, 1, 1));
		floor.addComponent<Engine::BoxCollider2D>()->width = 100;
		floor.getComponent<Engine::BoxCollider2D>()->height = floorSizeY / renderer.pixels_per_unit;
		floor.getComponent<Engine::Transform>()->translate(vec3(0, -10, 0));
		floor.getComponent<Engine::BoxCollider2D>()->friction = 0.5f;

		stoneGround.addComponent<Engine::Sprite>()->LoadSprite("Assets/stone.png");
		stoneGround.getComponent<Engine::Sprite>()->getMaterial().samplerMode = Engine::Material::SAMPLER_MODE_REPEAT;
		stoneGround.getComponent<Engine::Transform>()->scale(vec3(100, 5, 1));
		stoneGround.getComponent<Engine::Transform>()->translate(vec3(0, -13, 0));

		



		camera.addComponent<Engine::Camera>();
		camera.getComponent<Engine::Transform>()->translate(glm::vec3(0, 0, -10));

		Engine::SoundManager& sound = Engine::SoundManager::Get();
		sound.PlaySound();

		//world.create();
		
	}

	void GameScene::update() {
		Engine::Transform* transform = player.getComponent<Engine::Transform>();
		Engine::RigidBody2D* rigidbody = player.getComponent<Engine::RigidBody2D>();
		Engine::InputManager& input = Engine::InputManager::Get();
		if (input.GetKeyDown(SDL_SCANCODE_A)) {
			rigidbody->setVelocity(vec3(-10, rigidbody->velocity.y, 0));
			transform->scale(vec3(-1, 1, 1));
		}
		if (input.GetKeyDown(SDL_SCANCODE_D)) {
			rigidbody->setVelocity(vec3(10, rigidbody->velocity.y, 0));
			transform->scale(vec3(1, 1, 1));
		}
		if (input.GetKeyPressed(SDL_SCANCODE_SPACE)) {
			player.getComponent<Engine::RigidBody2D>()->addForce(glm::vec3(0, 1700.0f, 0));
		}
		if (input.GetKeyDown(SDL_SCANCODE_LEFT)){
			camera.getComponent<Engine::Transform>()->translate(vec3(-20, 0, 0) * Engine::Time::deltaTime);
		}
		if (input.GetKeyDown(SDL_SCANCODE_RIGHT)) {
			camera.getComponent<Engine::Transform>()->translate(vec3(20, 0, 0) * Engine::Time::deltaTime);
		}
		if (input.GetKeyDown(SDL_SCANCODE_UP)) {
			camera.getComponent<Engine::Transform>()->translate(vec3(0, 20, 0) * Engine::Time::deltaTime);
		}
		if (input.GetKeyDown(SDL_SCANCODE_DOWN)) {
			camera.getComponent<Engine::Transform>()->translate(vec3(0, -20, 0) * Engine::Time::deltaTime);
		}

	}
}