#include <Engine/CollisionManager.h>
#include <Engine/Time.h>

namespace Engine {

	int CollisionManager::addCollider(Collider2D* col) {
		colliders.push_back(col);
		return nextCollider++;
	}

	void CollisionManager::update() {
		for (auto& col : colliders) {

		}



	}
}