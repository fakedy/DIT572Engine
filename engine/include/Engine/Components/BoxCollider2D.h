#pragma once
#include <Engine/Components/Collider2D.h>
#include <Engine/GameObject.h>
#include <Engine/Renderer.h>


namespace Engine {
	class BoxCollider2D : public Collider2D {
	public:

		BoxCollider2D();
		~BoxCollider2D();

		bool ColliderCheck(Collider2D* other, Collider2D::CollisionStruct& colstruct) override;


		void onAdd() override;

		glm::vec2 getSize();
		void setSize(glm::vec2 size);


	private:

		glm::vec2 m_size{ 1,1 };
	};
}