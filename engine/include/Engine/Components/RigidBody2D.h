#pragma once
#include <glm/glm/glm.hpp>
#include <Engine/Components/Component.h>
#include <Engine/Components/Transform.h>

namespace Engine {
	class RigidBody2D : public Component {

		public:

			void setGravity(bool use);
			bool getGravity();

			RigidBody2D();
			~RigidBody2D() = default;

			void onAdd() override;

			int _RGbodyIndex{ -1 };
			Transform* _transform{ nullptr };

	private:
		float mass{ 1 };
			bool useGravity{ true };
			bool isKinematic{ false };
			glm::vec3 velocity{0.0f};

	};

}
