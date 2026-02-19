#pragma once
#include <Engine/Components/RigidBody2D.h>
#include <glm/glm/glm.hpp>


namespace Engine {
	class PhysicsManager {
	public:
		// singleton
		static PhysicsManager& Get() {
			static PhysicsManager instance;
			return instance;
		}


		void update();
		unsigned int addRGBody2D(RigidBody2D* rb);

		void removeRGBody2D(unsigned int index);


		glm::vec3 universeGravity = glm::vec3(0, -9.82f, 0);

	private:
		std::vector<RigidBody2D*> m_rgBodies2D;



	};

}