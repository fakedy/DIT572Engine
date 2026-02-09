#include <Engine/Components/RigidBody2D.h>
#include <Engine/Components/Transform.h>
#include <Engine/PhysicsManager.h>
#include <Engine/GameObject.h>

namespace Engine {

	

	void RigidBody2D::setGravity(bool use) {
		useGravity = use;
	}

	bool RigidBody2D::getGravity() {
		return useGravity;

	}

	glm::vec3 RigidBody2D::getVelocity()
	{
		return velocity;
	}

	void RigidBody2D::addForce(glm::fvec3 force)
	{
		acceleration = force / mass;
	}

	RigidBody2D::RigidBody2D(){

	}

	void RigidBody2D::onAdd() {

		// add itself to renderer
		_RGbodyIndex = PhysicsManager::Get().addRGBody2D(this);
		// Transform is default to gameobjects so they should have one.
		_transform = owner->getComponent<Transform>();
	}

}