#include <Engine/Components/Transform.h>




namespace Engine {

	void Transform::translate(glm::vec3 vec) {
		position = position + vec; // why not use glm translate here lol
	}


	void Transform::scale(glm::vec3 vec)
	{
	}

	void Transform::onAdd() {

	}
}

