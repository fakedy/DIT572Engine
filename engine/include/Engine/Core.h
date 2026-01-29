#pragma once
#include <vector>
#include <Engine/GameObject.h>
#include <Engine/InputManager.h>
#include <Engine/SoundManager.h>
#include <Engine/Time.h>
#include <Engine/Scene.h>


namespace Engine {

	class Core {
	public:



		Core();
		virtual ~Core();


		virtual void run();

		void setScene(Scene* scene);

	private:

		Scene* _scene;
		bool running{ true };
	};
}