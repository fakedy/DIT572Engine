#include <SDL3/SDL.h>
namespace Engine {

	class WindowManager {
	public:
		// singleton
		static WindowManager& Get() {
			static WindowManager instance;
			return instance;
		}

		WindowManager();

		~WindowManager() = default;

		int CreateWindow();

		int DestroyWindow();

		void swapBuffers();

		SDL_Window* getWindow();

	private:

		SDL_GLContext m_glContext;
		SDL_Window* m_window;
	};

}