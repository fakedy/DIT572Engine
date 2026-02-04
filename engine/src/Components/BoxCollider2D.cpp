#include <Engine/Components/BoxCollider2D.h>

namespace Engine {

	void BoxCollider2D::onAdd() {
		_colliderIndex = CollisionManager::Get().addCollider(this);
	}

	void BoxCollider2D::ColliderCheck(Collider2D* other) {
		// Implementation for 2D collision check
		if (other->type == BOX) {
			// Box-Box collision detection logic

		}
	}


}