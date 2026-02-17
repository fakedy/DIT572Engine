#pragma once
#include <Engine/Engine.h>

namespace Game {

	class World {
	public:
		static const int sizeX = 64;
		static const int sizeY = 16;
		int world[sizeX][sizeY];

		std::vector<Engine::GameObject*> worldObjects;
		World();
		~World() = default;

		void create();
	};
}