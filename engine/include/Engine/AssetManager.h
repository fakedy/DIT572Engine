#pragma once
#include <unordered_map>
#include <string>
#include <Engine/Texture.h>
#include <memory>


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

			std::shared_ptr<Texture> LoadTexture(const std::string& filePath);


		private:
			std::unordered_map<std::string, std::shared_ptr<Texture>> textureMap;
		};
	}