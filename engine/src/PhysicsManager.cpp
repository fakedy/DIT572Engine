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

			auto rbA = collision.rigidbodyA;
			auto rbB = collision.rigidbodyB;

			float resolveAmount = collision.penetrationDepth * 0.5f;

			bool moveA = (rbA != nullptr && !collision.rigidbodyA->isStatic);
			bool moveB = (rbB != nullptr && !collision.rigidbodyB->isStatic);

			if (!moveA && !moveB) {
				continue; // if both are static, do nothing
			}

			if (moveA) {
				collision.rigidbodyA->_transform->translate(collision.direction * resolveAmount);
				float dot = glm::dot(collision.direction, rbA->velocity);
				if (dot < 0) {
					rbA->velocity -= collision.direction * dot;
				}
			}

			if (moveB) {
				collision.rigidbodyB->_transform->translate(-collision.direction * resolveAmount);
				float dot = glm::dot(-collision.direction, rbB->velocity);
				if (dot > 0) {
					rbB->velocity -= -collision.direction * dot;
				}
			}



		}

	}
}