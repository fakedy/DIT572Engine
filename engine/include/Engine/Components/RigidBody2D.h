#pragma once
#include <glm/glm/glm.hpp>
#include <Engine/Components/Component.h>
#include <Engine/Components/Transform.h>

namespace Engine {
	class RigidBody2D : public Component {

	public:


		glm::vec3 getVelocity();
		
		void setVelocity(glm::vec3 velocity);

		void addForce(glm::fvec3 force);

		RigidBody2D();
		~RigidBody2D();

		void onAdd() override;

		int RGbodyIndex{ -1 };

		glm::fvec3 acceleration{ 0 };
		glm::vec3 velocity{0.0f};

		bool isStatic{ false };

		float friction{ 0 };
		bool affectedByGravity{ true };

		Transform* transform{ nullptr };

	private:
		float mass{ 1 };
		bool isKinematic{ false };


	};

}
