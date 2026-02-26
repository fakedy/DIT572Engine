#include <Engine/WindowManager.h>
#include <iostream>
namespace Engine {


	WindowManager::WindowManager() {

	}

	int WindowManager::CreateWindow() {

		// no support for multiple windows
		if (m_window != nullptr) {
			return 0;
		}


		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);


		// create window
		m_window = SDL_CreateWindow("Hello SDL Window", 1280, 720, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
		if (!m_window) {
			SDL_Log("Window Creation Failed: %s", SDL_GetError());
			return -1;
		}

		m_glContext = SDL_GL_CreateContext(m_window);
		SDL_GL_MakeCurrent(m_window, m_glContext);


		return 0; // success
	}

	int WindowManager::DestroyWindow() {
		SDL_GL_DestroyContext(m_glContext);
		SDL_DestroyWindow(m_window);
		return 0;
	}

	void WindowManager::swapBuffers() {
		SDL_GL_SwapWindow(m_window);
	}

	SDL_Window* WindowManager::getWindow()
	{
		return m_window;
	}


}