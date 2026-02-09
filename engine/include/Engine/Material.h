#pragma once
#include <Engine/Texture.h>
#include <memory>
#include <glm/glm/glm.hpp>
#include <string>

namespace Engine {

	class Material {
	public:

		unsigned int shaderID{ 0 };
		std::shared_ptr<Texture> texture;
		glm::vec4 diffuse{ 1.0f };
		std::string name;


	private:
	};
}