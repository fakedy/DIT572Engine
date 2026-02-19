#include <Engine/CollisionManager.h>
#include <Engine/Components/Collider2D.h>
#include <Engine/Time.h>



namespace Engine {

	unsigned int CollisionManager::addCollider(Collider2D* col) {
		m_colliders.push_back(col);
		return m_colliders.size() -1;
	}

	void CollisionManager::removeCollider(unsigned int index)
	{

		if (index >= m_colliders.size()) {
			return;
		}

		if (index != m_colliders.size() - 1) {
			m_colliders.back()->colliderIndex = index;
			m_colliders[index] = m_colliders.back();
		}
		m_colliders.pop_back();

	}



	std::vector<Collider2D::CollisionStruct> CollisionManager::update() {
		std::vector<Collider2D::CollisionStruct> collisions;
		
		// Amazing O(n^2) collision check
		for (auto& col : m_colliders) {
			for(auto& other : m_colliders) {
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