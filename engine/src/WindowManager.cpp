#include <Engine/WindowManager.h>
#include <iostream>
namespace Engine {


	WindowManager::WindowManager() {

	}

	int WindowManager::CreateWindow() {

		// no support for multiple windows
		if (_window != nullptr) {
			return 0;
		}

		// make sure SDL video is init
		if (!SDL_Init(SDL_INIT_VIDEO)) {
			SDL_Log("SDL_Init Failed: %s", SDL_GetError());
			return -1;
		}

		// create window
		_window = SDL_CreateWindow("Hello SDL Window", 1920, 1080, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		if (!_window) {
			SDL_Log("Window Creation Failed: %s", SDL_GetError());
			return -1;
		}

		_glContext = SDL_GL_CreateContext(_window);
		SDL_GL_MakeCurrent(_window, _glContext);


		return 0; // success
	}

	int WindowManager::DestroyWindow() {
		SDL_GL_DestroyContext(_glContext);
		SDL_DestroyWindow(_window);
		return 0;
	}

	void WindowManager::swapBuffers() {
		SDL_GL_SwapWindow(_window);
	}


}