#pragma once
#include <Engine/Components/Component.h>
#include <glm/glm/glm.hpp>



namespace Engine {

	class Transform : Component{
	public:
		glm::vec3 position;

	};

}