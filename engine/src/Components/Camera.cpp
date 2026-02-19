#include <Engine/Components/Camera.h>
#include <Engine/Renderer.h>
#include <glm/glm/gtc/matrix_transform.hpp>

namespace Engine {


	void Camera::onAdd() {
		_projection = glm::orthoZO(0.0f, 800.0f, 0.0f, 600.0f, 0.0f, 1.0f);
		_transform = owner->getComponent<Transform>();
		Renderer::Get().addCamera(this);
	}

	void Camera::updateProjection() {
		if (_projectionType == ProjectionType::Orthographic) {
			_projection = glm::orthoZO(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, -10.0f, 10.0f);
			_view = glm::translate(glm::mat4(1.0f), -_transform->getPosition() + glm::vec3(0,0,-10));
		}
		else {
			// perspective projection
		}
	}

	glm::mat4 Camera::getProjection() {
		updateProjection();
		return _projection * _view;
	}
}
