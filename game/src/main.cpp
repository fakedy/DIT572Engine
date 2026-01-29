#include <Engine/Core.h>
#include <Game/GameScene.h>

namespace Game {

	class Game : public Engine::Core {

	};

}

int main(){

	// create game class
	Game::Game game;
	
	// create game scene

	Game::GameScene* gameScene = new Game::GameScene();
	game.setScene(gameScene);
	// run the game
	game.run();
	
	return -1;
}