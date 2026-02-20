#pragma once
#include <Engine/Components/Component.h>
#include <Engine/GameObject.h>
#include <unordered_map>
#include <string>
namespace Engine
{
	class Animator : public Component {

		public:
			Animator() = default;
			~Animator() = default;

			void onAdd() override;

			void loadAnimations(std::string& folderPath);

			struct AnimationInfo {
				unsigned int startIndex{ 0 };
				unsigned int endIndex{ 0 };
				float frameRate{ 12.0f };
			};

			void playAnimation(const std::string& animationName, bool loop = false);

			AnimationInfo* currentAnimation;
			int currentFrameIndex = 0;
			float animationTime{ 0.0f };


			unsigned int index{ 0 };

			std::unordered_map<std::string, AnimationInfo> animationMap;

	};

}

