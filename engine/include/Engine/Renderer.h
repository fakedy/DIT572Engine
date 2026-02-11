#pragma once
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>
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

		~Renderer();

		int init();

		void draw();

		void drawSprite(glm::mat4 model, Material& texture);


		int addRenderObject(RenderComponent* sprite);
		void removeSprite(int id);

		void handleResizeWindow(unsigned int width, unsigned int height);

		SDL_GPUShader* createShader(const char* shaderPath, SDL_GPUShaderFormat format, SDL_GPUShaderStage stage
			, Uint32 numSamplers, Uint32 numUniformBuffers, Uint32 numStorageBuffers, Uint32 numStorageTextures);

		float pixels_per_unit{ 32.0f };
	private:




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

		SDL_GPUBuffer* quadVertexBuffer;
		SDL_GPUBuffer* quadIndicesBuffer;

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

		SDL_GPUDevice* _gpuDevice;

		SDL_GPUGraphicsPipeline* _spritePipeline;
		SDL_GPUGraphicsPipeline* _simple3DPipeline;

	};



}
