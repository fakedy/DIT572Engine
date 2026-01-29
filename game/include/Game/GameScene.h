#pragma once
#include <Engine/Engine.h>
#include <Engine/Scene.h>


namespace Game {

	class GameScene : public Engine::Scene {
	public:

		void start() override;
		void update() override;

	private:

	};
}