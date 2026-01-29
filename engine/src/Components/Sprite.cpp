#include <Engine/Components/Sprite.h>
#include <Engine/Renderer.h>
#include <iostream>
#include <glm/glm/gtc/matrix_transform.hpp>



namespace Engine {


	void Sprite::onAdd() {


		Renderer::Get().addSprite(this);
		// if there is no transform when you add a sprite its cooked
		transform = owner->getComponent<Transform>();
	}

	void Sprite::draw() {
		if (transform) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, transform->position);
			/*
				float scaleX = texture->width / pixels_per_unit;
				float scaleY = texture->height / pixels_per_unit
				model = glm::scale(model, glm::vec3(scaleX, scaleY, 1.0f);
			*/
			Renderer::Get().drawSprite(model);
		}
	}
}