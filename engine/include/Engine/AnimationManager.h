#pragma once
#include <vector>


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

	private:
		std::vector<Animator*> m_animator;
	};
}