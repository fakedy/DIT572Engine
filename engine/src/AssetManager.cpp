#include <Engine/AssetManager.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>
#include <Engine/Renderer.h>
#include <SDL3/SDL_gpu.h>

namespace Engine {
	AssetManager::AssetManager() {

	}

	std::shared_ptr<Texture> AssetManager::LoadTexture(const std::string& filePath) {

		//guh singletons
		SDL_GPUDevice& device = Renderer::Get().getDevice();

		if (m_textureMap.find(filePath) != m_textureMap.end()) {
			return m_textureMap[filePath];
		}

		int w, h, channels;
		
		stbi_set_flip_vertically_on_load(true);
		stbi_uc *pixels = stbi_load(filePath.c_str(), &w, &h, &channels, 4);
		
		SDL_GPUTextureCreateInfo textureInfo = {};
		textureInfo.props = 0;
		textureInfo.width = w;
		textureInfo.height = h;
		textureInfo.type = SDL_GPU_TEXTURETYPE_2D_ARRAY;
		textureInfo.format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM;
		textureInfo.layer_count_or_depth = 1;
		textureInfo.num_levels = 1;
		textureInfo.usage = SDL_GPU_TEXTUREUSAGE_SAMPLER;

		SDL_GPUTexture* texture = SDL_CreateGPUTexture(&device, &textureInfo);

		// this is similar to renderer, its the basic way to upload stuff to the gpu using SDL_GPU









		SDL_GPUTransferBufferCreateInfo bufferCreateInfo = {};
		bufferCreateInfo.props = 0;
		bufferCreateInfo.size = w * h * 4;
		bufferCreateInfo.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD;

		SDL_GPUTransferBuffer* textureTransferBuffer = SDL_CreateGPUTransferBuffer(&device, &bufferCreateInfo);


		void* textureTransferPtr = SDL_MapGPUTransferBuffer(&device, textureTransferBuffer, false);
		SDL_memcpy(textureTransferPtr, pixels, bufferCreateInfo.size);
		SDL_UnmapGPUTransferBuffer(&device, textureTransferBuffer);


		SDL_GPUTextureTransferInfo source = {};
		source.transfer_buffer = textureTransferBuffer;
		source.offset = 0;

		SDL_GPUTextureRegion destination = {};
		destination.texture = texture;
		destination.w = w;
		destination.h = h;
		destination.d = 1;


		// memcpy part


		SDL_GPUCommandBuffer* uploadCmdBuffer = SDL_AcquireGPUCommandBuffer(&device);
		SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(uploadCmdBuffer);

		SDL_UploadToGPUTexture(copyPass, &source, &destination, false);

		SDL_EndGPUCopyPass(copyPass);
		SDL_SubmitGPUCommandBuffer(uploadCmdBuffer);
		SDL_ReleaseGPUTransferBuffer(&device, textureTransferBuffer);


		std::shared_ptr<Texture> newTexture = std::make_shared<Texture>();
		newTexture->filepath = filePath;
		newTexture->textureHandle = texture;
		newTexture->width = w;
		newTexture->height = h;

		stbi_image_free(pixels);
		m_textureMap[filePath] = newTexture;

		return m_textureMap[filePath];
	}
	std::shared_ptr<Material> Engine::AssetManager::CreateMaterial(const std::string& name)
	{
		if (m_materialmap.find(name) != m_materialmap.end()) {
			return m_materialmap[name];
		}

		std::shared_ptr<Material> newMaterial = std::make_shared<Material>();
		newMaterial->name = name;
		m_materialmap[name] = newMaterial;
		return m_materialmap[name];

	}


	std::shared_ptr<Texture> AssetManager::LoadTextureArray(const std::vector<std::string>& filePaths) {

		//guh singletons
		SDL_GPUDevice& device = Renderer::Get().getDevice();

		/*
		if (m_textureMap.find(filePath) != m_textureMap.end()) {
			return m_textureMap[filePath];
		}
		*/

		int w, h, channels;

		stbi_set_flip_vertically_on_load(true);

		stbi_info(filePaths[0].c_str(), &w, &h, &channels);

		SDL_GPUTextureCreateInfo textureInfo = {};
		textureInfo.props = 0;
		textureInfo.width = w;
		textureInfo.height = h;
		textureInfo.type = SDL_GPU_TEXTURETYPE_2D_ARRAY;
		textureInfo.format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM;
		textureInfo.num_levels = 1;
		textureInfo.usage = SDL_GPU_TEXTUREUSAGE_SAMPLER;


		textureInfo.layer_count_or_depth = filePaths.size();

		SDL_GPUTexture* texture = SDL_CreateGPUTexture(&device, &textureInfo);

		// this is similar to renderer, its the basic way to upload stuff to the gpu using SDL_GPU

		uint32_t imageSizeInBytes = w * h * 4;

		SDL_GPUTransferBufferCreateInfo bufferCreateInfo = {};
		bufferCreateInfo.props = 0;
		bufferCreateInfo.size = imageSizeInBytes * filePaths.size();
		bufferCreateInfo.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD;

		SDL_GPUTransferBuffer* textureTransferBuffer = SDL_CreateGPUTransferBuffer(&device, &bufferCreateInfo);
		uint8_t* textureTransferPtr = static_cast<Uint8*>(SDL_MapGPUTransferBuffer(&device, textureTransferBuffer, false));


		unsigned int count = 0;
		for (const auto& path : filePaths) {
			SDL_Log(path.c_str());
			stbi_uc* pixels = stbi_load(path.c_str(), &w, &h, &channels, 4);
			if (pixels == nullptr) {
				SDL_Log("pixels nullptr");
				return nullptr;
			}

			uint32_t offset = count * imageSizeInBytes; // offset of image + the count
			SDL_memcpy(textureTransferPtr + offset, pixels, imageSizeInBytes);

			stbi_image_free(pixels);
			count++;
		}

		SDL_UnmapGPUTransferBuffer(&device, textureTransferBuffer);

		SDL_GPUCommandBuffer* uploadCmdBuffer = SDL_AcquireGPUCommandBuffer(&device);
		SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(uploadCmdBuffer);

		unsigned int layer = 0;
		for (const auto& path : filePaths) {

			SDL_GPUTextureTransferInfo source = {};
			source.transfer_buffer = textureTransferBuffer;
			source.offset = layer * imageSizeInBytes;

			SDL_GPUTextureRegion destination = {};
			destination.texture = texture;
			destination.w = w;
			destination.h = h;
			destination.d = 1;
			destination.layer = layer;

			SDL_UploadToGPUTexture(copyPass, &source, &destination, false);
			layer++;
		}

		SDL_EndGPUCopyPass(copyPass);
		SDL_SubmitGPUCommandBuffer(uploadCmdBuffer);
		SDL_ReleaseGPUTransferBuffer(&device, textureTransferBuffer);


		std::shared_ptr<Texture> newTexture = std::make_shared<Texture>();
		newTexture->filepath = "höhö";
		newTexture->textureHandle = texture;
		newTexture->width = w;
		newTexture->height = h;

		//m_textureMap[filePath] = newTexture;

		return newTexture;
	}
}