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
			~Animator();

			void onAdd() override;

			void loadAnimations(const std::string& folderPath);

			struct AnimationInfo {
				unsigned int startIndex{ 0 };
				unsigned int endIndex{ 0 };
				float frameRate{ 3.0f };
				std::string name;
			};

			void playAnimation(const std::string& animationName,bool override, float fps, bool loop = false);

			void update();

			
			AnimationInfo* currentAnimation;
			int currentFrameIndex = 0;
			float animationTime{ 0.0f };

			bool isPlaying{ false };
			bool loops{ false };
			unsigned int playCount{0};

			unsigned int index{ 0 };

			std::unordered_map<std::string, AnimationInfo> animationMap;

	};

}

