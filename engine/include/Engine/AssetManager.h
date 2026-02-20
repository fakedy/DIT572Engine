#pragma once
#include <unordered_map>
#include <string>
#include <Engine/Texture.h>
#include <memory>
#include <Engine/Material.h>
#include <SDL3/SDL_gpu.h>


namespace Engine {
	class AssetManager {
		public:
			// singleton
			static AssetManager& Get() {
				static AssetManager instance;
				return instance;
			}

			AssetManager();
			~AssetManager() = default;

			/**
			* @brief Loads a texture from the disk into GPU memory and store the Texture Object in a map.
			* * @param filePath The relative path to the asset (e.g., "Assets/Brick.png").
			* @return Shared_ptr<Texture> if successful.
			*/
			std::shared_ptr<Texture> LoadTexture(const std::string& filePath);


			/**
			* @brief Creates a material for the given texture name
			* * @param filePath The relative path to the asset (e.g., "Assets/Brick.png").
			* @return Shared_ptr<Material> if successful.
			*/
			std::shared_ptr<Material> CreateMaterial(const std::string& name);

			std::shared_ptr<Texture> LoadTextureArray(const std::vector<std::string>& filePaths);


		private:
			std::unordered_map<std::string, std::shared_ptr<Texture>> m_textureMap;
			std::unordered_map<std::string, std::shared_ptr<Material>> m_materialmap;
		};
	}