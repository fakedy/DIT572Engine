#include <Engine/Components/Animator.h>
#include <filesystem>
#include <SDL3/SDL.h>
#include <vector>
#include <Engine/AssetManager.h>
#include <Engine/AnimationManager.h>

namespace Engine {

	void Animator::onAdd()
	{
	}
	void Animator::loadAnimations(std::string& folderPath)
	{
		SDL_Log("Loading animation");

		// for every folder?

		namespace fs = std::filesystem;
		int frameCount = 0;
		int folderCounter = 0;

		std::vector<std::string> framePaths;

		for (const auto& entry : fs::directory_iterator(folderPath)) {

			folderCounter++;
			AnimationInfo info;
			info.startIndex = frameCount;
			info.name = entry.path().filename().string();

			for (const auto& file : fs::directory_iterator(entry.path())) {
				if (!file.is_regular_file()) {
					continue;
				}


				SDL_Log("Reading file: %s", file.path().filename().string().c_str());
				frameCount++;
				framePaths.push_back(file.path().string());
			}

			std::string folderName = entry.path().filename().string();

			SDL_Log("Folder: %s", folderName.c_str());
		

			info.endIndex = frameCount;


			animationMap[folderName] = info;

		}

		std::shared_ptr<Texture> texture = AssetManager::Get().LoadTextureArray(framePaths);
		owner->getComponent<Sprite>()->getMaterial().texture = texture;

		AnimationManager::Get().addAnimator(this);

	}

	void Animator::playAnimation(const std::string& animationName,bool override,float fps, bool loop)
	{


		auto& it = animationMap.find(animationName);
		if (it == animationMap.end()) {
			SDL_Log("Animation %s not found!", animationName.c_str());
			return;
		}

		if (currentAnimation != nullptr && it->second.name == currentAnimation->name && isPlaying) {
			return;
		}

		if (isPlaying && !override) {
			return;
		}



		isPlaying = true;
		
		currentAnimation = &it->second;
		currentAnimation->frameRate = fps;

		animationTime = 0.0f;
		currentFrameIndex = currentAnimation->startIndex;
	}
	void Engine::Animator::play()
	{

		owner->getComponent<Sprite>()->spriteIndex = currentFrameIndex;
	}
}
