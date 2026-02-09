#include <Engine/Components/BoxCollider2D.h>
#include <Engine/CollisionManager.h>
#include <Engine/Renderer.h>
#include <glm/glm/ext/matrix_transform.hpp>

namespace Engine {



	void BoxCollider2D::onAdd() {
		_colliderIndex = CollisionManager::Get().addCollider(this);
		_transform = owner->getComponent<Transform>();
	}

	bool BoxCollider2D::ColliderCheck(Collider2D* other, Collider2D::CollisionStruct& colstruct) {
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

			if(collisionX && collisionY) {
				// Collision detected
				float overlapX = std::min(aMaxX, bMaxX) - std::max(aMinX, bMinX); // Calculate overlap on X axis
				float overlapY = std::min(aMaxY, bMaxY) - std::max(aMinY, bMinY); // Calculate overlap on Y axis

				colstruct.colA = this; // Set the colliding boxes
				colstruct.colB = other;

				if (overlapX < overlapY) {
					colstruct.penetrationDepth = overlapX; // Set penetration depth
					colstruct.direction = _transform->getPosition().x < other->_transform->getPosition().x ? glm::vec3(-1, 0, 0) : glm::vec3(1, 0, 0); // Set collision direction
				} else {
					colstruct.penetrationDepth = overlapY;
					colstruct.direction = _transform->getPosition().y < other->_transform->getPosition().y ? glm::vec3(0, -1, 0) : glm::vec3(0, 1, 0);
				}
				return true;
			} 
		}
		return false;
	}

	void BoxCollider2D::drawCollider(Renderer* renderer) {
		if(_transform){
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, _transform->getPosition());

			renderer->drawLines(model, glm::vec3(1.0f, 0.0f, 0.0f));
		}

	}


}