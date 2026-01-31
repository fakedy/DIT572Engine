#include <game/World.h>


namespace Game {

	World::World()
	{

		for (size_t x = 0; x < sizeX; x++)
		{
			for (size_t y = 0; y < sizeY; y++)
			{

				world[x][y] = 1;

			}
		}

	}



	void World::create() {

		for (size_t x = 0; x < sizeX; x++)
		{
			for (size_t y = 0; y < sizeY; y++)
			{

				auto* block = new Engine::GameObject();
				block->addComponent<Engine::Sprite>()->LoadSprite("Assets/stone.png");
				worldObjects.push_back(block);
				block->getComponent<Engine::Transform>()->translate(glm::vec3(x - (sizeX/2.0f), y - (sizeY*1.2f), 0.0f));

			}
		}
	}
}