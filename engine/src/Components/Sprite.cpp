#include <Engine/Components/Sprite.h>
#include <Engine/Renderer.h>
#include <iostream>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <Engine/AssetManager.h>

namespace Engine {

	Sprite::Sprite() {



	}

	Sprite::~Sprite()
	{
		Renderer::Get().removeSprite(_renderIndex);

	}

	Sprite::Sprite(const char* path) {
	}

	void Sprite::onAdd() {

		// add itself to renderer
		_renderIndex = Renderer::Get().addRenderObject(this);
		// Transform is default to gameobjects so they should have one.
		_transform = owner->getComponent<Transform>();
	}

	void Sprite::draw() {

	}

	glm::mat4 Sprite::getModel()
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, _transform->getPosition());
		model = glm::scale(model, _transform->getScale());

		// set uvScale since it might be used
		// could use a separate function to get it but whatever
		uvScale = glm::vec2(_transform->getScale().x, _transform->getScale().y);

		return model;
	}

	Material& Sprite::getMaterial()
	{
		return *material.get();
	}

	void Sprite::LoadSprite(const char* path) {
		// temp way to do this
		std::shared_ptr<Texture> texture = AssetManager::Get().LoadTexture(path);
		material = AssetManager::Get().CreateMaterial(path);
		material->texture = texture;
	}
}