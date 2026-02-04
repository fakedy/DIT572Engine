#pragma once
#include <glm/glm/glm.hpp>
#include <Engine/Components/Component.h>
#include <Engine/CollisionManager.h>

namespace Engine {
	class Collider2D : public Component{
		public:
			virtual void ColliderCheck(Collider2D* other) = 0;


			enum ColliderType2D{
				BOX,
				CIRCLE
			};

			int _colliderIndex{ -1 };

			ColliderType2D type{ BOX };
	};
}