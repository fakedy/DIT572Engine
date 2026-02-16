#pragma once
#include <Engine/Components/Component.h>
#include <Engine/Components/Transform.h>
#include <glm/glm/glm.hpp>

namespace Engine {
	class Camera : public Component {
		public:
			enum class ProjectionType {
				Perspective,
				Orthographic
			};

			void onAdd() override;
			
			glm::mat4 getProjection() const;

			void updateProjection();

			bool isActive{ true };

			float orthoWidth{ 800.0f };
			float orthoHeight{ 600.0f };

			Transform* _transform{ nullptr };

		private:
			glm::mat4 _projection{ 1.0f };
			ProjectionType _projectionType{ ProjectionType::Orthographic };
	};

}