#pragma once 
#include <Engine/Components/Component.h>
#include <Engine/Material.h>



namespace Engine {
	class RenderComponent : public Component {
	public:


		virtual void draw() = 0;

	private:



	};
}