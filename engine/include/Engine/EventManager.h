#pragma once
#include <SDL3/SDL.h>

namespace Engine {
	class EventManager {
	public:
		// singleton
		static EventManager& Get() {
			static EventManager instance;
			return instance;
		}

		EventManager() = default;

		~EventManager() = default;

		void PollEvents(bool& running);

	private:
	};
}