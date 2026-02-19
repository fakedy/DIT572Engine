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
			
			glm::mat4 getProjection();

			glm::mat4 getView();

			void updateProjection();

			bool isActive{ true };

			float orthoWidth{ 800.0f };
			float orthoHeight{ 600.0f };


		private:

			Transform* m_transform{ nullptr };
			glm::mat4 m_projection{ 1.0f };
			glm::mat4 m_view{ 1.0f };
			ProjectionType m_projectionType{ ProjectionType::Orthographic };
	};

}