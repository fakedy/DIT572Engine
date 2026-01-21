#include <Game/GameLayer.h>
#include <Engine/GameObject.h>
#include <Engine/InputManager.h>
#include <iostream>


// this is the heart of the game
namespace Game {
	using namespace glm;

	Engine::GameObject player;




	void GameLayer::start() {
		std::cout << "Hello World!\n";
		player.addComponent<Engine::Transform>();
	}

	void GameLayer::update() {
		Engine::Transform* transform = player.getComponent<Engine::Transform>();
		transform->position = vec3(0, 0, 0);
		Engine::InputManager& input = Engine::InputManager::Get();
	}
}