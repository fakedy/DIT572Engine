#include <Engine/PhysicsManager.h>
#include <Engine/Time.h>
#include <Engine/CollisionManager.h>
#include <Engine/Components/Collider2D.h>

namespace Engine {

	Engine::CollisionManager& cm = Engine::CollisionManager::Get();

	unsigned int PhysicsManager::addRGBody2D(RigidBody2D* rb) {
		rgBodies2D.push_back(rb);
		return rgBodies2D.size() - 1;
	}

	void PhysicsManager::removeRGBody2D(unsigned int index)
	{
		// if valid
		if (index >= rgBodies2D.size())
			return;

		if (index != rgBodies2D.size() - 1) {
			rgBodies2D.back()->RGbodyIndex = index;
			rgBodies2D[index] = rgBodies2D.back();
		}
		rgBodies2D.pop_back();
	}


	void PhysicsManager::update() {

		// Apply gravity

		for (auto& rb : rgBodies2D) {
			if (!rb->affectedByGravity || rb->isStatic) {
				continue;
			}

			rb->acceleration += universeGravity;
			rb->velocity += rb->acceleration * Time::deltaTime;
			rb->transform->translate(rb->getVelocity() * Time::deltaTime);

			// reset acceleration
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
				collision.rigidbodyA->transform->translate(collision.direction * resolveAmount);
				float dot = glm::dot(collision.direction, rbA->velocity);
				// kill the velocity going into the floor
				if (dot < 0) {
					//rbA->velocity -= collision.direction * dot;
				}
			}

			if (moveB) {
				collision.rigidbodyB->transform->translate(-collision.direction * resolveAmount);
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