#include <Engine/Components/Animator.h>
#include <filesystem>
#include <SDL3/SDL.h>


void Engine::Animator::onAdd()
{
}
void Engine::Animator::loadAnimations(std::string& folderPath)
{
	SDL_Log("Loading animation");

	// for every folder?

	namespace fs = std::filesystem;
	int frameCount = 0;
	int folderCounter = 0;

	for (const auto& entry : fs::directory_iterator(folderPath)) {

		folderCounter++;
		AnimationInfo info;
		info.startIndex = frameCount;

		for (const auto& file : fs::directory_iterator(entry.path())) {
			frameCount++;
		}



		std::string folderName = entry.path().filename().string();

		SDL_Log("Folder: %s", folderName.c_str());
		

		info.endIndex = frameCount;
		frameCount++;

		animationMap[folderName] = info;

	}


	// create animationInfo
	// start from sprite 0 to max files in folder
	// once we've created all animationInfo
	// somehow send this to assetmanager and create a 2d texture array
	// the correct index need to be preserved or animations break






}
