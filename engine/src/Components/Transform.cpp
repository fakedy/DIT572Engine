#include <Engine/Components/Transform.h>




namespace Engine {

	void Transform::translate(const glm::vec3& pos) {
		m_position += pos;
	}


	void Transform::scale(const glm::vec3& scale)
	{
		m_scale = scale;

	}

	void Transform::onAdd() {

	}


	glm::vec3 Transform::getPosition() const
	{
		return m_position;
	}

	void Transform::setPosition(const glm::vec3 pos)
	{

		m_position = pos;
	}

	glm::vec3 Transform::getScale() const
	{
		return m_scale;


	}

}