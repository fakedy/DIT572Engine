#pragma once
#include <Engine/Components/Component.h>
#include <glm/glm/glm.hpp>



namespace Engine {

	class Transform : public Component{
	public:
		glm::vec3 position{ 0.0f };
		glm::vec3 scale{ 0.0f };

		/**
		* @brief translate the transform
		* * @param Vec3 value
		*/
		void translate(glm::vec3 vec);


		/**
		* @brief Scale the transform
		* * @param Vec3 value
		*/
		void scale(glm::vec3 vec);



		void onAdd() override;

	};

}