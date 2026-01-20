#pragma once
#include <glad/glad.h>
#include <SDL3/SDL.h>

namespace Engine {

	class Renderer {
	public:

		static Renderer& Get() {
			static Renderer instance;
			return instance;
		}

		int init();


		void clear();

	};



}
