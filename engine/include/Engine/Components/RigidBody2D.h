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
		~RigidBody2D() = default;

		void onAdd() override;

		int _RGbodyIndex{ -1 };
		Transform* _transform{ nullptr };

		glm::fvec3 acceleration{ 0 };
		glm::vec3 velocity{0.0f};

		bool isStatic{ false };

		float friction{ 0 };
		bool affectedByGravity{ true };

	private:
		float mass{ 1 };
		bool isKinematic{ false };


	};

}
