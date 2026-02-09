#include <Engine/Components/BoxCollider2D.h>
#include <Engine/CollisionManager.h>

namespace Engine {

	void BoxCollider2D::onAdd() {
		_colliderIndex = CollisionManager::Get().addCollider(this);
		_transform = owner->getComponent<Transform>();
	}

	bool BoxCollider2D::ColliderCheck(Collider2D* other) {
		// Implementation for 2D collision check
		if (other->type == BOX) {
			// Box-Box collision detection logic
			BoxCollider2D* otherBox = static_cast<BoxCollider2D*>(other);

			float aMinX = _transform->getPosition().x - width / 2;
			float aMaxX = _transform->getPosition().x + width / 2;
			float aMinY = _transform->getPosition().y - height / 2;
			float aMaxY = _transform->getPosition().y + height / 2;

			float bMinX = otherBox->_transform->getPosition().x - otherBox->width / 2;
			float bMaxX = otherBox->_transform->getPosition().x + otherBox->width / 2;
			float bMinY = otherBox->_transform->getPosition().y - otherBox->height / 2;
			float bMaxY = otherBox->_transform->getPosition().y + otherBox->height / 2;

			bool collisionX = aMaxX > bMinX && aMinX < bMaxX;
			bool collisionY = aMaxY > bMinY && aMinY < bMaxY;

			if(collisionX || collisionY) {
				// Collision detected
				return true;
			} 
		}
		return false;
	}


}