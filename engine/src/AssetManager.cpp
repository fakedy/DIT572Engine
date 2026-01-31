#include <Engine/AssetManager.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>
#include <glad/glad.h>

namespace Engine {
	AssetManager::AssetManager() {

	}

	std::shared_ptr<Texture> AssetManager::LoadTexture(const std::string& filePath) {
		int w, h, channels;

		stbi_uc *pixels = stbi_load(filePath.c_str(), &w, &h, &channels, 0);

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		if (!pixels) {
			std::cout << "Failed to load texture file: " << filePath << std::endl;
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		std::shared_ptr<Texture> newTexture = std::make_shared<Texture>();
		newTexture->id = texture;
		newTexture->width = w;
		newTexture->height = h;

		stbi_image_free(pixels);
		textureMap[filePath] = newTexture;

		return textureMap[filePath];
	}
}