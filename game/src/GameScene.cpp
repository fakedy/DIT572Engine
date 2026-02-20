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

	/*
		With current grass setup the floor is actually at -8.5
		Putting sprites at correct locations by code is suprisingly annoying
	*/



	
	void GameScene::start() {
		Engine::Renderer& renderer = Engine::Renderer::Get();
		renderer.pixels_per_unit = 16.0f;
		player.addComponent<Engine::Sprite>()->LoadSprite("Assets/Sprites/Slime/slime_0.png");
		float playerSizeX = player.getComponent<Engine::Sprite>()->getMaterial().texture->width;
		float playerSizeY = player.getComponent<Engine::Sprite>()->getMaterial().texture->height;
		player.addComponent<Engine::BoxCollider2D>()->setSize(glm::vec2(playerSizeX / renderer.pixels_per_unit, playerSizeY / renderer.pixels_per_unit));
		player.addComponent<Engine::RigidBody2D>();
		player.getComponent<Engine::Transform>()->scale(vec3(-1, 1, 1));
		player.getComponent<Engine::Transform>()->translate(vec3(0, 0, 5));


		box.addComponent<Engine::Sprite>()->LoadSprite("Assets/Sprites/box.png");
		box.getComponent<Engine::Transform>()->translate(vec3(6, 0, 0));
		box.addComponent<Engine::RigidBody2D>();

		float boxSizeX = box.getComponent<Engine::Sprite>()->getMaterial().texture->width;
		float boxSizeY = box.getComponent<Engine::Sprite>()->getMaterial().texture->height;
		box.addComponent<Engine::BoxCollider2D>()->setSize(glm::vec2(boxSizeX / renderer.pixels_per_unit, boxSizeY / renderer.pixels_per_unit));
		box.getComponent<Engine::BoxCollider2D>()->friction = 0.5f;
		box.addComponent<Engine::RigidBody2D>();

		box2.addComponent<Engine::Sprite>()->LoadSprite("Assets/Sprites/box.png");
		box2.getComponent<Engine::Transform>()->translate(vec3(3, -8.5, 6));

		box3.addComponent<Engine::Sprite>()->LoadSprite("Assets/Sprites/box.png");
		box3.getComponent<Engine::Transform>()->translate(vec3(-3, -8.5, 4));

		sky.addComponent<Engine::Sprite>()->LoadSprite("Assets/Sprites/sky.png");
		sky.getComponent<Engine::Transform>()->translate(vec3(0, 47, -3));
		sky.getComponent<Engine::Transform>()->scale(vec3(10000, 1, 1));

		floor.addComponent<Engine::Sprite>()->LoadSprite("Assets/Sprites/grass_stone.png");
		floor.getComponent<Engine::Sprite>()->getMaterial().samplerMode = Engine::Material::SAMPLER_MODE_REPEAT;
		float floorSizeX = floor.getComponent<Engine::Sprite>()->getMaterial().texture->width;
		float floorSizeY = floor.getComponent<Engine::Sprite>()->getMaterial().texture->height;
		floor.getComponent<Engine::Transform>()->scale(vec3(100, 1, 1));
		floor.addComponent<Engine::BoxCollider2D>()->setSize(glm::vec2(100, floorSizeY / renderer.pixels_per_unit));
		floor.getComponent<Engine::Transform>()->translate(vec3(0, -10, 0));
		floor.getComponent<Engine::BoxCollider2D>()->friction = 0.5f;

		stoneGround.addComponent<Engine::Sprite>()->LoadSprite("Assets/Sprites/stone.png");
		stoneGround.getComponent<Engine::Sprite>()->getMaterial().samplerMode = Engine::Material::SAMPLER_MODE_REPEAT;
		stoneGround.getComponent<Engine::Transform>()->scale(vec3(100, 7, 1));
		stoneGround.getComponent<Engine::Transform>()->translate(vec3(0, -14, 0));

		
		cloud.addComponent<Engine::Sprite>()->LoadSprite("Assets/Sprites/cloud.png");
		cloud.getComponent<Engine::Transform>()->translate(vec3(14, 13, 0));

		cloud2.addComponent<Engine::Sprite>()->LoadSprite("Assets/Sprites/cloud.png");
		cloud2.getComponent<Engine::Transform>()->translate(vec3(-16, 12, -2));
		cloud2.getComponent<Engine::Transform>()->scale(vec3(0.5, 0.5, 1));

		badbg.addComponent<Engine::Sprite>()->LoadSprite("Assets/Sprites/badbg.png");
		badbg.getComponent<Engine::Transform>()->translate(vec3(0, 17, -1));



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

		if (input.GetKeyPressed(SDL_SCANCODE_F1)) {
			SDL_Log("Player Position: (%f, %f, %f)", transform->getPosition().x, transform->getPosition().y, transform->getPosition().z);
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

		// for some camera y-axis follow on camera
		Engine::Transform* cameraTransform = camera.getComponent<Engine::Transform>();
		if (transform->getPosition().y >= 5) {
			cameraTransform->setPosition(
				glm::vec3(
					cameraTransform->getPosition().x,
					transform->getPosition().y - 5,
					cameraTransform->getPosition().z));
		}
		else {
			cameraTransform->setPosition(glm::vec3(0,0,-10));
		}

	}
}
