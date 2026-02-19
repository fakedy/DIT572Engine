#include <Engine/Components/RigidBody2D.h>
#include <Engine/Components/Transform.h>
#include <Engine/PhysicsManager.h>
#include <Engine/GameObject.h>

namespace Engine {

	

	glm::vec3 RigidBody2D::getVelocity()
	{
		return velocity;
	}

	void RigidBody2D::setVelocity(glm::vec3 velocity)
	{
		this->velocity = velocity;
	}

	void RigidBody2D::addForce(glm::fvec3 force)
	{
		acceleration = force / mass;
	}

	RigidBody2D::RigidBody2D(){

	}

	RigidBody2D::~RigidBody2D()
	{
		PhysicsManager::Get().removeRGBody2D(RGbodyIndex);
	}

	void RigidBody2D::onAdd() {

		// add itself to renderer
		RGbodyIndex = PhysicsManager::Get().addRGBody2D(this);
		// Transform is default to gameobjects so they should have one.
		transform = owner->getComponent<Transform>();
	}

}