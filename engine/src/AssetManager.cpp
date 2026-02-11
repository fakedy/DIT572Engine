#include <Engine/AssetManager.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>
#include <glad/glad.h>

namespace Engine {
	AssetManager::AssetManager() {

	}

	std::shared_ptr<Texture> AssetManager::LoadTexture(const std::string& filePath) {


		if (textureMap.find(filePath) != textureMap.end()) {
			return textureMap[filePath];
		}

		int w, h, channels;
		
		stbi_set_flip_vertically_on_load(true);
		stbi_uc *pixels = stbi_load(filePath.c_str(), &w, &h, &channels, 0);

		unsigned int texture;
		std::shared_ptr<Texture> newTexture = std::make_shared<Texture>();
		newTexture->filepath = filePath;
		newTexture->id = 0;
		newTexture->width = w;
		newTexture->height = h;

		stbi_image_free(pixels);
		textureMap[filePath] = newTexture;

		return textureMap[filePath];
	}
	std::shared_ptr<Material> Engine::AssetManager::CreateMaterial(const std::string& name)
	{
		if (materialmap.find(name) != materialmap.end()) {
			return materialmap[name];
		}

		std::shared_ptr<Material> newMaterial = std::make_shared<Material>();
		newMaterial->name = name;
		materialmap[name] = newMaterial;
		return materialmap[name];

	}
}