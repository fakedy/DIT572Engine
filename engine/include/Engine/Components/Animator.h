#pragma once
#include <Engine/Components/Component.h>

namespace Engine
{
	class Animator : public Component {

		public:
			Animator();
			~Animator();

			void onAdd() override;

			float animationTime{ 0.0f };


	};

}

