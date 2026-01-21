#pragma once
#include <Engine/Components/Transform.h>
#include <Engine/Components/Sprite.h>
#include <vector>


namespace Engine {

	class GameObject {
	public:


		~GameObject() {

			for (auto* component : components) {
				delete component;
			}
			components.clear();
		}

		// add a component
		template <typename T>
		T* addComponent() {
			// create new component of T
			T* component = new T();
			components.push_back(component);
			return component;
		}

		// return pointer to component
		template <typename T>
		T* getComponent() {

			for (auto* component : components) {
				// try cast component to T*
				T* ptr = dynamic_cast<T*>(component);
				
				// if success
				if (ptr != nullptr) {
					return ptr;
				}
			}
			return nullptr;
		}


	private:

		std::vector<Component*> components;

	};

}