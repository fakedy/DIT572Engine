#pragma once
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <Engine/Shader.h>

namespace Engine {

	class Renderer {
	public:

		// singleton
		static Renderer& Get() {
			static Renderer instance;
			return instance;
		}

		int init();

		void draw();

		void clear();

	};



}
