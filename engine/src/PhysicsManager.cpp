#include <Engine/PhysicsManager.h>
#include <Engine/Time.h>

namespace Engine {

	int PhysicsManager::addRGBody2D(RigidBody2D* rb) {
		rgBodies2D.push_back(rb);
		return nextRGBody2D++;
	}

	void PhysicsManager::update() {
		for (auto& rb : rgBodies2D) {
			if (rb->getGravity()) {
				rb->_transform->translate(rb->_transform->getPosition() + glm::vec3(0.0f, gravity * Time::deltaTime, 0.0f));
			}
		}



	}
}