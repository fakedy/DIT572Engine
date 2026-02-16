#include <Engine/components/Camera.h>
#include <Engine/Renderer.h>
#include <glm/glm/gtc/matrix_transform.hpp>

namespace Engine {


	void Camera::onAdd() {
		_projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f) ;
		_transform = owner->getComponent<Transform>();
		Renderer::Get().addCamera(this);
	}

	void Camera::updateProjection() {
		if (_projectionType == ProjectionType::Orthographic) {
			_projection = glm::ortho(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight);
			_projection = glm::translate(_projection, -_transform->getPosition());
		}
		else {
			// perspective projection
		}
	}

	glm::mat4 Camera::getProjection() {
		updateProjection();
		return _projection;
	}
}