#include <Engine/Components/Camera.h>
#include <Engine/Renderer.h>
#include <glm/glm/gtc/matrix_transform.hpp>

namespace Engine {
	Camera::~Camera()
	{
		Renderer::Get().removeCamera(index);

	}
	void Camera::onAdd() {
		m_projection = glm::orthoZO(0.0f, 800.0f, 0.0f, 600.0f, 0.0f, 1.0f);
		m_transform = owner->getComponent<Transform>();
		index = Renderer::Get().addCamera(this);
	}

	void Camera::updateProjection() {
		if (m_projectionType == ProjectionType::Orthographic) {
			m_projection = glm::orthoZO(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, -10.0f, 10.0f);
			m_view = glm::translate(glm::mat4(1.0f), -m_transform->getPosition() + glm::vec3(0,0,-10));
		}
		else {
			// perspective projection
		}
	}

	glm::mat4 Camera::getProjection() {
		updateProjection();
		return m_projection;
	}
	glm::mat4 Camera::getView()
	{
		return m_view;
	}
}
