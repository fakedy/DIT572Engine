#pragma once
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <Engine/Shader.h>
#include <Engine/Components/Sprite.h>
#include <unordered_map>
#include <Engine/Texture.h>
#include <Engine/Components/RenderComponent.h>
namespace Engine {

	class Renderer {
	public:

		// singleton
		static Renderer& Get() {
			static Renderer* instance = new Renderer();
			return *instance;
		}

		Renderer();

		int init();

		void draw();

		void drawSprite(glm::mat4 model, Material& texture);


		void clear();

		int addRenderObject(RenderComponent* sprite);
		void removeSprite(int id);

		void handleResizeWindow(unsigned int width, unsigned int height);


		float pixels_per_unit{ 32.0f };
	private:


		Shader defaultShader = Shader("assets/vDefault.vs", "assets/fDefault.fs");


		// Quad Vertices
		float vertices[20] = {
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f 
		};

		// Quad indices
		const unsigned int indices[6] = {
			0, 1, 3,
			1, 2, 3
		};

		unsigned int VAO;
		unsigned int VBO;
		unsigned int EBO;

		std::unordered_map<int,RenderComponent*> RenderObjects;
		int nextRenderObject{ 0 };

		unsigned int windowHeight = 720;
		unsigned int windowWidth = 1280;
		float unitHeight = 30.0f;

		// temporary projection matrix
		glm::mat4 proj;

	};



}
