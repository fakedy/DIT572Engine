#pragma once
#include <Engine/Components/Component.h>
#include <Engine/Components/Transform.h>
#include <Engine/Components/RenderComponent.h>
#include <Engine/GameObject.h>
#include <memory>
#include <Engine/Texture.h>
#include <Engine/Material.h>

namespace Engine {

	class Sprite : public RenderComponent{
	public:

		Sprite();
		~Sprite();
		Sprite(const char* path);

		Transform* _transform{ nullptr };

		void draw();

		void LoadSprite(const char* path);

		void onAdd() override;
	private:


		std::shared_ptr<Material> material;
		int _renderIndex{ 0 };

	};
}