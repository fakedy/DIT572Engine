#pragma once
#include <Engine/Components/Component.h>
#include <glm/glm/glm.hpp>



namespace Engine {

	class Transform : public Component{
	public:

		/**
		* @brief translate the transform
		* * @param Vec3 value
		*/
		void translate(const glm::vec3& pos);

		/**
		* @brief Scale the transform
		* * @param Vec3 value
		*/
		void scale(const glm::vec3& scale);

		/**
		* @brief Return a reference to position
		* * @return glm::vec3& position
		*/
		glm::vec3 getPosition() const;

		void setPosition(glm::vec3 pos);

		glm::vec3 getScale() const;

		void onAdd() override;
	private:
		glm::vec3 m_position{ 0.0f };
		glm::vec3 m_scale{ 1.0f };

		glm::mat4 m_cachedTransform{ 1.0f };
	};

}