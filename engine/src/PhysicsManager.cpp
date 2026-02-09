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
				rb->_transform->translate(glm::vec3(0.0f, gravity * Time::deltaTime, 0.0f));
			}
		}

		std::vector<Collider2D::CollisionStruct> list = cm.update();
		for (auto& collision : list) {
			// Simple collision response
			float resolveAmount = collision.penetrationDepth * 0.5f;
			collision.colA->_transform->translate(collision.direction * resolveAmount);
		}

	}
}