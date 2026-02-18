#include <Engine/CollisionManager.h>
#include <Engine/Components/Collider2D.h>
#include <Engine/Time.h>



namespace Engine {

	unsigned int CollisionManager::addCollider(Collider2D* col) {
		colliders.push_back(col);
		return colliders.size() -1;
	}

	void CollisionManager::removeCollider(unsigned int index)
	{

		if (index >= colliders.size()) {
			return;
		}

		if (index != colliders.size() - 1) {
			colliders.back()->_colliderIndex = index;
			colliders[index] = colliders.back();
		}
		colliders.pop_back();

	}



	std::vector<Collider2D::CollisionStruct> CollisionManager::update() {
		std::vector<Collider2D::CollisionStruct> collisions;
		
		// Amazing O(n^2) collision check
		for (auto& col : colliders) {
			for(auto& other : colliders) {
				if (col != other) {
					Collider2D::CollisionStruct colstruct;

					if (col->ColliderCheck(other, colstruct)) {
						collisions.push_back(colstruct);
					}
				}
			}



		}
			

		return collisions;

	}
}