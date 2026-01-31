#pragma once
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <Engine/Shader.h>
#include <Engine/Components/Sprite.h>
#include <unordered_map>
#include <Engine/Texture.h>
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

		void drawSprite(glm::mat4 model, Texture& texture);

		void clear();

		int addSprite(Sprite* sprite);
		void removeSprite(int id);

		void handleResizeWindow(int width, int height);


	private:
		Shader defaultShader = Shader("assets/vDefault.vs", "assets/fDefault.fs");


		float vertices[20] = {
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f 
		};

		const unsigned int indices[6] = {
			0, 1, 3,
			1, 2, 3
		};

		unsigned int VAO;
		unsigned int VBO;
		unsigned int EBO;

		std::unordered_map<int,Sprite*> spriteMap;
		int nextSprite{ 0 };

		int windowHeight = 720;
		int windowWidth = 1280;

		float pixels_per_unit{ 32.0f };

		glm::mat4 proj;

	};



}
