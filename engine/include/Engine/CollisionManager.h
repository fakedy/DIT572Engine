#pragma once
#include <Engine/Components/Collider2D.h>
#include <glm/glm/glm.hpp>
#include <vector>


namespace Engine {
	class CollisionManager {
		public:


			static CollisionManager& Get() {
				static CollisionManager instance;
				return instance;
			}

			std::vector<Collider2D::CollisionStruct> update();
			unsigned int addCollider(Collider2D* col);


			/**
			* @brief Removes a collider from the collisionManager
			* * @param index of collider in the collider vector
			*/
			void removeCollider(unsigned int index);


		private:
			std::vector<Collider2D*> m_colliders;
			bool m_isTrigger{ false };
	};
}