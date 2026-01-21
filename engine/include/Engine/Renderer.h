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


	private:
		Shader defaultShader = Shader("vDefault.vs", "fDefault.fs");


		const float vertices[18] = {
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 
			-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f 
		};

		unsigned int VAO;
		unsigned int VBO;





	};



}
