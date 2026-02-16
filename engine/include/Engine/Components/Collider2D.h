#pragma once
#include <Engine/Components/Component.h>
#include <Engine/Components/Transform.h>
#include <engine/Components/RigidBody2D.h>

namespace Engine {
	class Collider2D : public Component{
		public:

			struct CollisionStruct {
				RigidBody2D* rigidbodyA;
				RigidBody2D* rigidbodyB;
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