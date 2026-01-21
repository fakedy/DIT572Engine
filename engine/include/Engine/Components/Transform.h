#pragma once
#include <Engine/Components/Component.h>
#include <glm/glm/glm.hpp>



namespace Engine {

	class Transform : public Component{
	public:
		glm::vec3 position;

	};

}