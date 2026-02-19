#pragma once 
#include <Engine/Components/Component.h>
#include <Engine/Material.h>
#include <glm/glm/glm.hpp>



namespace Engine {
	class RenderComponent : public Component {
	public:


		virtual void draw() = 0;
		virtual glm::mat4 getModel() = 0;
		virtual Material& getMaterial() = 0;

		glm::vec2 uvScale = glm::vec2(1, 1);
		unsigned int renderIndex{ 0 };
		

	protected:
		std::shared_ptr<Material> m_material;
	private:

	};
}