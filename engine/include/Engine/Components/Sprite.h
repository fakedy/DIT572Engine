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

		Transform* transform{ nullptr };

		void draw() override;
		glm::mat4 getModel() override;
		Material& getMaterial() override;

		void LoadSprite(const char* path);

		void onAdd() override;

		unsigned int spriteIndex{ 0 };

	private:



	};
}