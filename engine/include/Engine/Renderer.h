#pragma once
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>
#include <Engine/Components/Sprite.h>
#include <vector>
#include <Engine/Texture.h>
#include <Engine/Components/RenderComponent.h>
#include <Engine/Components/Camera.h>
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


		SDL_GPUDevice& getDevice();

		unsigned int addSpriteObject(Sprite* object);
		void removeSpriteObject(unsigned int id);

		void handleResizeWindow(unsigned int width, unsigned int height);

		SDL_GPUShader* createShader(const char* shaderPath, SDL_GPUShaderFormat format, SDL_GPUShaderStage stage
			, Uint32 numSamplers, Uint32 numUniformBuffers, Uint32 numStorageBuffers, Uint32 numStorageTextures);

		float pixels_per_unit{ 32.0f };

		unsigned int addCamera(Camera* camera);
		void removeCamera(unsigned int index);

	private:


		void setupSpritePipeline();
		void setupPostFXPipeline();

		void createSamplers();

		// Quad Vertices
		float m_vertices[20] = {
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f 
		};

		// Quad indices
		const uint16_t m_indices[6] = {
			0, 1, 3,
			1, 2, 3
		};

		SDL_GPUBuffer* m_quadVertexBuffer;
		SDL_GPUBuffer* m_quadIndicesBuffer;

		SDL_GPUSampler* m_samplerNearest;
		SDL_GPUSampler* m_samplerLinear;
		SDL_GPUSampler* m_samplerRepeat;


		SDL_GPUTexture* m_depthTexture;
		SDL_GPUTexture* m_postFXTexture;

		std::vector<Sprite*> m_spriteObjects;

		std::vector<Sprite*> m_spriteOpaqueQueue;
		std::vector<Sprite*> m_spriteTransparentQueue;


		int m_nextRenderObject{ 0 };

		std::vector<Camera*> m_cameras;


		unsigned int m_windowHeight = 720;
		unsigned int m_windowWidth = 1280;
		float m_unitHeight = 34.0f;

		SDL_GPUDevice* m_gpuDevice;

		SDL_GPUGraphicsPipeline* m_spritePipeline;
		SDL_GPUGraphicsPipeline* m_postFXPipeline;

	};



}
