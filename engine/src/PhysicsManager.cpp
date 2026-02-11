#include <Engine/PhysicsManager.h>
#include <Engine/Time.h>
#include <Engine/CollisionManager.h>
#include <Engine/Components/Collider2D.h>

namespace Engine {

	Engine::CollisionManager& cm = Engine::CollisionManager::Get();

	int PhysicsManager::addRGBody2D(RigidBody2D* rb) {
		rgBodies2D.push_back(rb);
		return nextRGBody2D++;
	}

	void PhysicsManager::update() {
		for (auto& rb : rgBodies2D) {
			if (rb->getGravity()) {
				rb->acceleration += + glm::vec3(0, -9.82f, 0);
				rb->velocity += rb->acceleration * Time::deltaTime;
				rb->_transform->translate(rb->getVelocity() * Time::deltaTime);
			}
			rb->acceleration = glm::vec3(0);
		}

		std::vector<Collider2D::CollisionStruct> list = cm.update();
		for (auto& collision : list) {
			// Simple collision response
			collision.rigidbodyA->velocity = glm::vec3(0); // set acceleration to 0, not very accurate.
			float resolveAmount = collision.penetrationDepth * 0.5f;
			collision.rigidbodyA->_transform->translate(collision.direction * resolveAmount);
		}

	}
}