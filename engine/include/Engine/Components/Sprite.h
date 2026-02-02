#pragma once
#include <Engine/Components/Component.h>
#include <Engine/Components/Transform.h>
#include <Engine/GameObject.h>
#include <memory>
#include <Engine/Texture.h>


namespace Engine {

	class Sprite : public Component{
	public:

		Sprite();
		~Sprite();
		Sprite(const char* path);

		Transform* _transform{ nullptr };

		// like this or something
		//Texture* texture{ nullptr };


		void onAdd() override;

		void draw();

		void LoadSprite(const char* path);

	private:
		std::shared_ptr<Texture> texture;

		int _renderIndex{ 0 };
	};
}