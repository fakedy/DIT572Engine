#include <Engine/Renderer.h>


namespace Engine {


	int Renderer::init() {


		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
			SDL_Log("Failed to initialize GLAD");
			return -1;
		}
		return 0;
	}


	void Renderer::draw() {

	}


	void Renderer::clear() {
		glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}



}