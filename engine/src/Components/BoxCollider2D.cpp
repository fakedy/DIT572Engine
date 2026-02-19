#include <Engine/Components/BoxCollider2D.h>
#include <Engine/CollisionManager.h>
#include <Engine/Renderer.h>
#include <glm/glm/ext/matrix_transform.hpp>

namespace Engine {



	void BoxCollider2D::onAdd() {
		colliderIndex = CollisionManager::Get().addCollider(this);
		_transform = owner->getComponent<Transform>();
	}

	glm::vec2 BoxCollider2D::getSize() const
	{
		return m_size;
	}

	void BoxCollider2D::setSize(glm::vec2 size)
	{
		m_size = size;
	}

	BoxCollider2D::BoxCollider2D()
	{
		type = ColliderType2D::BOX;
	}

	BoxCollider2D::~BoxCollider2D()
	{

		CollisionManager::Get().removeCollider(colliderIndex);

	}

	bool BoxCollider2D::ColliderCheck(Collider2D* other, Collider2D::CollisionStruct& colstruct) {
		// Implementation for 2D collision check
		if (other->type == BOX) {
			// Box-Box collision detection logic
			BoxCollider2D* otherBox = static_cast<BoxCollider2D*>(other);

			float aMinX = _transform->getPosition().x - m_size.x / 2;
			float aMaxX = _transform->getPosition().x + m_size.x / 2;
			float aMinY = _transform->getPosition().y - m_size.y / 2;
			float aMaxY = _transform->getPosition().y + m_size.y / 2;

			float bMinX = otherBox->_transform->getPosition().x - otherBox->getSize().x / 2;
			float bMaxX = otherBox->_transform->getPosition().x + otherBox->getSize().x / 2;
			float bMinY = otherBox->_transform->getPosition().y - otherBox->getSize().y / 2;
			float bMaxY = otherBox->_transform->getPosition().y + otherBox->getSize().y / 2;

			bool collisionX = aMaxX > bMinX && aMinX < bMaxX;
			bool collisionY = aMaxY > bMinY && aMinY < bMaxY;

			if(collisionX && collisionY) {
				// Collision detected
				float overlapX = std::min(aMaxX, bMaxX) - std::max(aMinX, bMinX); // Calculate overlap on X axis
				float overlapY = std::min(aMaxY, bMaxY) - std::max(aMinY, bMinY); // Calculate overlap on Y axis

				colstruct.rigidbodyA = this->owner->getComponent<RigidBody2D>(); // Set the colliding boxes
				colstruct.rigidbodyB = other->owner->getComponent<RigidBody2D>();
				colstruct.colliderA = this;
				colstruct.colliderB = other;

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




}