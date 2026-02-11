#pragma once
#include <string>
#include <SDL3/SDL_gpu.h>



namespace Engine {


	class Texture {
	public:

		Texture() = default;
		~Texture() = default;

		std::string filepath;
		SDL_GPUTexture* textureHandle = nullptr;
		SDL_GPUSampler* samplerHandle = nullptr;
		unsigned int width;
		unsigned int height;

	};
}