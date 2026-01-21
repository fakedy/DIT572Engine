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

		Renderer() {
			if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
				SDL_Log("Failed to initialize GLAD");
			}

			defaultShader.createShader();

		}

		int init();

		void draw();

		void clear();


	private:
		Shader defaultShader = Shader("assets/vDefault.vs", "assets/fDefault.fs");


		const float vertices[18] = {
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 
			-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f 
		};

		unsigned int VAO;
		unsigned int VBO;





	};



}
