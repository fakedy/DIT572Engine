#pragma once
#include <Engine/Components/Component.h>
#include <Engine/Components/Transform.h>
#include <Engine/GameObject.h>


namespace Engine {

	class Sprite : public Component{
	public:

		Transform* transform{ nullptr };

		void onAdd() override;

		void draw();


	};
}