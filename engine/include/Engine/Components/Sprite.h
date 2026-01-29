#pragma once
#include <Engine/Components/Component.h>
#include <Engine/Components/Transform.h>
#include <Engine/GameObject.h>


namespace Engine {

	class Sprite : public Component{
	public:

		Sprite();
		Sprite(const char* path);

		Transform* transform{ nullptr };

		// like this or something
		//Texture* texture{ nullptr };

		float pixels_per_unit{ 16.0f };

		void onAdd() override;

		void draw();


	};
}