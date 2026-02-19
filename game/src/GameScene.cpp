#include <Game/GameScene.h>
#include <iostream>

// this is the heart of the game
namespace Game {
	using namespace glm;

	Engine::GameObject player;

	Engine::GameObject box;
	Engine::GameObject box2;
	Engine::GameObject box3;

	Engine::GameObject cloud;
	Engine::GameObject cloud2;

	Engine::GameObject sky;

	Engine::GameObject badbg;



	Engine::GameObject floor;
	Engine::GameObject stoneGround;

	Engine::GameObject camera;
	
	void GameScene::start() {
		Engine::Renderer& renderer = Engine::Renderer::Get();
		renderer.pixels_per_unit = 16.0f;
		player.addComponent<Engine::Sprite>()->LoadSprite("Assets/Sprites/Slime/slime_0.png");
		float playerSizeX = player.getComponent<Engine::Sprite>()->material->texture->width;
		float playerSizeY = player.getComponent<Engine::Sprite>()->material->texture->height;
		player.addComponent<Engine::BoxCollider2D>()->width = playerSizeX / renderer.pixels_per_unit;
		player.getComponent<Engine::BoxCollider2D>()->height = playerSizeY / renderer.pixels_per_unit;
		player.addComponent<Engine::RigidBody2D>();
		player.getComponent<Engine::Transform>()->scale(vec3(-1, 1, 1));
		player.getComponent<Engine::Transform>()->translate(vec3(0, 0, 5));


		box.addComponent<Engine::Sprite>()->LoadSprite("Assets/Sprites/box.png");
		box.getComponent<Engine::Transform>()->translate(vec3(6, 0, 0));
		box.addComponent<Engine::RigidBody2D>();

		float boxSizeX = box.getComponent<Engine::Sprite>()->material->texture->width;
		float boxSizeY = box.getComponent<Engine::Sprite>()->material->texture->height;
		box.addComponent<Engine::BoxCollider2D>()->width = boxSizeX / renderer.pixels_per_unit;
		box.getComponent<Engine::BoxCollider2D>()->height = boxSizeY / renderer.pixels_per_unit;
		box.getComponent<Engine::BoxCollider2D>()->friction = 0.5f;
		box.addComponent<Engine::RigidBody2D>();

		box2.addComponent<Engine::Sprite>()->LoadSprite("Assets/Sprites/bbox.png");
		box2.getComponent<Engine::Transform>()->translate(vec3(3, -8.5, 6));

		box3.addComponent<Engine::Sprite>()->LoadSprite("Assets/Sprites/bbox.png");
		box3.getComponent<Engine::Transform>()->translate(vec3(-3, -8.5, 4));

		sky.addComponent<Engine::Sprite>()->LoadSprite("Assets/Sprites/bsky.png");
		sky.getComponent<Engine::Transform>()->translate(vec3(0, 47, -1));
		sky.getComponent<Engine::Transform>()->scale(vec3(10000, 1, 1));

		floor.addComponent<Engine::Sprite>()->LoadSprite("Assets/Sprites/bgrass_stone.png");
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
		stoneGround.getComponent<Engine::Transform>()->scale(vec3(100, 10, 1));
		stoneGround.getComponent<Engine::Transform>()->translate(vec3(0, -15, 0));

		
		cloud.addComponent<Engine::Sprite>()->LoadSprite("Assets/Sprites/bcloud.png");
		cloud.getComponent<Engine::Transform>()->translate(vec3(14, 13, 0));

		cloud2.addComponent<Engine::Sprite>()->LoadSprite("Assets/Sprites/bcloud.png");
		cloud2.getComponent<Engine::Transform>()->translate(vec3(-11, 15, 0));

		badbg.addComponent<Engine::Sprite>()->LoadSprite("Assets/Sprites/bbadbg.png");
		badbg.getComponent<Engine::Transform>()->translate(vec3(0, 17, 0));



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

		//camera.getComponent<Engine::Transform>()->setPosition(glm::vec3(transform->getPosition().x, transform->getPosition().y+5, -10));

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

		Engine::Transform* cloudTransform = cloud.getComponent<Engine::Transform>();
		Engine::Transform* cloud2Transform = cloud2.getComponent<Engine::Transform>();

		cloudTransform->translate(vec3(1, 0, 0) * Engine::Time::deltaTime * 0.2f);
		cloud2Transform->translate(vec3(1, 0, 0) * Engine::Time::deltaTime * 0.5f);
		// just move clouds if they go offscreen
		if (cloudTransform->getPosition().x > 44) {
			cloudTransform->setPosition(glm::vec3( - 44, cloudTransform->getPosition().y, cloudTransform->getPosition().z));
		}
		if (cloud2Transform->getPosition().x > 44) {
			cloud2Transform->setPosition(glm::vec3(-44, cloud2Transform->getPosition().y, cloud2Transform->getPosition().z));
		}

	}
}
