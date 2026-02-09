#pragma once
#include <glm/glm/glm.hpp>
#include <Engine/Components/Component.h>
#include <Engine/Components/Transform.h>

namespace Engine {
	class RigidBody2D : public Component {

	public:

		void setGravity(bool use);
		bool getGravity();

		glm::vec3 getVelocity();

		void addForce(glm::fvec3 force);

		RigidBody2D();
		~RigidBody2D() = default;

		void onAdd() override;

		int _RGbodyIndex{ -1 };
		Transform* _transform{ nullptr };

		glm::fvec3 acceleration{ 0 };
		glm::vec3 velocity{0.0f};
	private:
		float mass{ 1 };
		bool useGravity{ true };
		bool isKinematic{ false };

	};

}
