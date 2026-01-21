#pragma once
#include <SDL3/SDL.h>

namespace Engine {

	class SoundManager {
	public:
		// singleton
		static SoundManager& Get() {
			static SoundManager instance;
			return instance;
		}

		SoundManager();

		~SoundManager() =default;

		void PlaySound();

		void StopSound();


	};
}