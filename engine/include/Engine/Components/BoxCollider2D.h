#pragma once
#include <Engine/Components/Collider2D.h>


namespace Engine {
	class BoxCollider2D : public Collider2D {
	public:
		bool ColliderCheck(Collider2D* other) override;

		void onAdd() override;

		BoxCollider2D() {type = ColliderType2D::BOX; }



	private:
		
		float width{ 1.0f };
		float height{ 1.0f };
	};
}