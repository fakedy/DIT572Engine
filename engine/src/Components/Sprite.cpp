#include <Engine/Components/Sprite.h>
#include <Engine/Renderer.h>
#include <iostream>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <Engine/AssetManager.h>

namespace Engine {

	Sprite::Sprite() {

	}

	Sprite::Sprite(const char* path) {
	}

	void Sprite::onAdd() {


		Renderer::Get().addSprite(this);
		// if there is no transform when you add a sprite its cooked
		transform = owner->getComponent<Transform>();
	}

	void Sprite::draw() {
		if (transform) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, transform->position);
			Renderer::Get().drawSprite(model, *texture.get());
		}
	}

	void Sprite::LoadSprite(const char* path) {
		texture = AssetManager::Get().LoadTexture(path);
		std::cout << "Sprite object: " << texture.get()->width << std::endl;
	}
}