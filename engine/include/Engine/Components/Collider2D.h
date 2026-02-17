#pragma once
#include <Engine/Components/Component.h>
#include <Engine/Components/Transform.h>
#include <Engine/Components/RigidBody2D.h>

namespace Engine {
	class Collider2D : public Component{
		public:

			struct CollisionStruct {
				RigidBody2D* rigidbodyA;
				Collider2D* colliderA;
				RigidBody2D* rigidbodyB;
				Collider2D* colliderB;
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

			float friction{ 0 };

			ColliderType2D type{ BOX };
	};
}