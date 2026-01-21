#pragma once
#include <Engine/Components/Transform.h>
#include <Engine/Components/Sprite.h>



namespace Engine {

	class GameObject {
	public:

		// add a component
		template <typename T>
		void addComponent(T) {

		}

		// return pointer to component
		template <typename T>
		T* getComponent() {
			return nullptr;
		}


	private:



	};

}