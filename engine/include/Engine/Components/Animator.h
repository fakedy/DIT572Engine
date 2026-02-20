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
				float frameRate{ 24.0f };
				std::string name;
			};

			void playAnimation(const std::string& animationName, bool loop = false);

			void play();

			
			AnimationInfo* currentAnimation;
			int currentFrameIndex = 0;
			float animationTime{ 0.0f };

			bool isPlaying{ false };

			unsigned int index{ 0 };

			std::unordered_map<std::string, AnimationInfo> animationMap;

	};

}

