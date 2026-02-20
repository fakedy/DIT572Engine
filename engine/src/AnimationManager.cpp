#include <Engine/AnimationManager.h>
#include <Engine/Components/Animator.h>
#include <Engine/Time.h>
#include <SDL3/SDL.h>

namespace Engine {
	void AnimationManager::Update() {
		for (auto& animator : m_animators)
		{
			if (animator->currentAnimation == nullptr) {
				continue;
			}
			
			animator->animationTime += Time::deltaTime;

			float frameDuration = 1.0 / animator->currentAnimation->frameRate;

			if (animator->animationTime >= frameDuration) {
				animator->animationTime = 0.0f;

				if (animator->currentFrameIndex >= animator->currentAnimation->endIndex) {
					animator->currentFrameIndex = animator->currentAnimation->startIndex;
					animator->isPlaying = false;
				}

				animator->currentFrameIndex++;

			}
			animator->play();
			SDL_Log("Name: %s, Index: %d", animator->currentAnimation->name.c_str(), animator->currentFrameIndex);

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