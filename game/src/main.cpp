#include <Engine/Core.h>
#include <Game/GameLayer.h>

namespace Game {

	class Game : public Engine::Core {





	};




}

int main(){

	Game::Game game;
	Game::GameLayer* gameLayer = new Game::GameLayer;

	game.addLayer(gameLayer);

	game.run();
	
	return -1;
}