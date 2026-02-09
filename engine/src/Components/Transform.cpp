#include <Engine/Components/Transform.h>




namespace Engine {

	void Transform::translate(const glm::vec3& pos) {
		_position = _position + pos; // why not use glm translate here lol
	}


	void Transform::scale(const glm::vec3& scale)
	{
		_scale = scale;

	}

	void Transform::onAdd() {

	}


	glm::vec3 Transform::getPosition() const
	{
		return _position;
	}

	glm::vec3 Transform::getScale() const
	{
		return _scale;


	}

}