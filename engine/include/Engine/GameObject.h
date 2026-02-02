#pragma once
#include <Engine/Components/Transform.h>
#include <Engine/Components/Sprite.h>
#include <vector>



namespace Engine {

	class GameObject {
	public:

		GameObject() {
			this->addComponent<Transform>();
		}

		~GameObject() {

			for (auto* component : components) {
				delete component;
			}
			components.clear();
		}

		/**
		* @brief Adds a component to the GameObject. Ensures its unique across the GameObject.
		* * @tparam T Type of compononent. Class derived from Component
		* @return T* pointer to newly created component.
		*/
		template <typename T>
		T* addComponent() {
			
			if (hasComponent<T>()) {
				return getComponent<T>();
			}

			// create new component of T
			T* component = new T();
			components.push_back(component);
			component->owner = this;
			component->onAdd();
			return component;
		}

		/**
		* @brief Get component of type T from GameObject
		* * @tparam T Type of compononent. Class derived from Component
		* @return T* pointer to the component. @c nullptr if it doesnt exist.
		*/
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

		template <typename T>
		bool hasComponent() {
			return getComponent<T>() != nullptr;
		}


	private:

		std::vector<Component*> components;

	};

}