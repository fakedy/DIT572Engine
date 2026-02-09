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
			int addCollider(Collider2D* col);

			std::vector<Collider2D*> colliders;
			int nextCollider{ 0 };

		private:
			bool isTrigger{ false };
	};
}