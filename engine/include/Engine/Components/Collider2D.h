#pragma once
#include <Engine/Components/Component.h>

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