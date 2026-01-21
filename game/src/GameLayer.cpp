#include <Game/GameLayer.h>
#include <Engine/GameObject.h>
#include <iostream>


// this is the heart of the game
namespace Game {


	
	Engine::GameObject player;




	void GameLayer::start() {
		std::cout << "Hello World!\n";
		player.addComponent<Engine::Transform>();
	}

	void GameLayer::update() {
		Engine::Transform* transform = player.getComponent<Engine::Transform>();
		transform->position = glm::vec3(0, 0, 0);

	}
}