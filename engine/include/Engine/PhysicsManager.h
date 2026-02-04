#pragma once
#include <Engine/Components/RigidBody2D.h>

namespace Engine {
	class PhysicsManager {
	public:
		// singleton
		static PhysicsManager& Get() {
			static PhysicsManager instance;
			return instance;
		}


		void update();
		int addRGBody2D(RigidBody2D* rb);

		std::vector<RigidBody2D*> rgBodies2D;
		int nextRGBody2D{ 0 };


		float gravity{ -9.82f };
	};




}