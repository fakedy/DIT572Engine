#pragma once
#include <Engine/Components/Component.h>
#include <Engine/Components/Transform.h>

namespace Engine {
	class Collider2D : public Component{
		public:

			struct CollisionStruct {
				Collider2D* colA;
				Collider2D* colB;
				float penetrationDepth;
				glm::vec3 direction;
			};

			virtual bool ColliderCheck(Collider2D* other, CollisionStruct& colstruct) = 0;

			Transform* _transform{ nullptr };

			enum ColliderType2D{
				BOX,
				CIRCLE
			};

			int _colliderIndex{ -1 };

			ColliderType2D type{ BOX };
	};
}