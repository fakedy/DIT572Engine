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

			void removeCollider(unsigned int index);

			std::vector<Collider2D*> colliders;

		private:
			bool m_isTrigger{ false };
	};
}