#include <Engine/AnimationManager.h>
#include <Engine/Components/Animator.h>

namespace Engine {
	AnimationManager::AnimationManager() {
	}

	void AnimationManager::Update() {
		for (auto& animator : m_animators)
		{
			// fuffens



		}
	}

	unsigned int AnimationManager::addAnimator(Animator* anim) {
		m_animators.push_back(anim);
		return m_animators.size() - 1;
	}

	void AnimationManager::removeAnimator(unsigned int index) {
		if (index >= m_animators.size()) {
			return;
		}

		if (index != m_animators.size() - 1) {
			m_animators.back()->index = index;
			m_animators[index] = m_animators.back();
		}
		m_animators.pop_back();

	}
}