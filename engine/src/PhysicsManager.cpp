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
				if(rb->isStatic){
					continue; // if static, do not apply gravity or move
				}

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
				// kill the velocity going into the floor
				if (dot < 0) {
					//rbA->velocity -= collision.direction * dot;
				}
			}

			if (moveB) {
				collision.rigidbodyB->_transform->translate(-collision.direction * resolveAmount);
				float dot = glm::dot(-collision.direction, rbB->velocity);
				// kill the velocity going into the floor
				if (dot > 0) {
					//rbB->velocity -= -collision.direction * dot;
				}
			}

			if (rbA != nullptr && collision.colliderB != nullptr) {
				float dot = glm::dot(collision.direction, glm::vec3(0,1,0));
				if (dot > 0.5) {
					rbA->velocity *= (1 - collision.colliderB->friction);
				}
			}

			if (rbB != nullptr && collision.colliderA != nullptr) {
				float dot = glm::dot(-collision.direction, glm::vec3(0, 1, 0));
				if (dot > 0.5) {
					rbB->velocity *= (1 - collision.colliderA->friction);
				}

			}



		}

	}
}