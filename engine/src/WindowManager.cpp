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


		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);


		// create window
		_window = SDL_CreateWindow("Hello SDL Window", 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
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

	SDL_Window* WindowManager::getWindow()
	{
		return _window;
	}


}