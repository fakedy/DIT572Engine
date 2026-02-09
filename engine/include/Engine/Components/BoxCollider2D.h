#pragma once
#include <Engine/Components/Collider2D.h>
#include <Engine/GameObject.h>
#include <Engine/Renderer.h>


namespace Engine {
	class BoxCollider2D : public Collider2D {
	public:
		bool ColliderCheck(Collider2D* other, Collider2D::CollisionStruct& colstruct) override;


		void onAdd() override;

		BoxCollider2D() {type = ColliderType2D::BOX; }

		float width{ 1.0f };
		float height{ 1.0f };

	private:

	};
}