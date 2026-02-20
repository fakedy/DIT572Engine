#pragma once
#include <vector>
#include <Engine/Components/Animator.h>
#include <Engine/Texture.h>

namespace Engine
{
	class AnimationManager {
	public:

		// singleton
		static AnimationManager& Get() {
			static AnimationManager instance;
			return instance;
		}

		AnimationManager();
		~AnimationManager() = default;

		void Update();

		unsigned int addAnimator(Animator* anim);

		void removeAnimator(unsigned int index);

		Texture* animationTexture;

	private:
		std::vector<Animator*> m_animators;
	};
}