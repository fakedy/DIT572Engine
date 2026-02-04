#pragma once
#include <Engine/Texture.h>
#include <memory>


namespace Engine {

	class Material {
	public:

		unsigned int shaderID{ 0 };
		std::shared_ptr<Texture> texture;

	private:
	};
}