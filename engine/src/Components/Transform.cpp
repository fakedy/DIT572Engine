#include <Engine/Components/Transform.h>




namespace Engine {

	void Transform::translate(glm::vec3 vec) {
		position = position + vec;
	}


	void Transform::onAdd() {

	}
}

