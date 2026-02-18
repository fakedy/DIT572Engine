#include <Engine/Scene.h>
#include <Engine/Engine.h>





namespace Server {

	class Level : public Engine::Scene {

	public:

		void start() override;
		void update() override;

	private:

	};
}