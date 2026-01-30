#pragma once
#include <unordered_map>
#include <string>


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

			int LoadTexture(const std::string& filePath);


		private:
			std::unordered_map<std::string, unsigned int> textureMap;
		};
	}