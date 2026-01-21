#include <Engine/Core.h>
#include <Game/GameLayer.h>
#include <Engine/WindowManager.h>

namespace Game {

	class Game : public Engine::Core {

	};

}

int main(){

	// create game class
	Game::Game game;

	// create the game layer
	Game::GameLayer* gameLayer = new Game::GameLayer;

	// add layer to engine
	game.addLayer(gameLayer);

	// run the game
	game.run();
	
	return -1;
}