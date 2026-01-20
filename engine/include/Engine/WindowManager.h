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

	private:

		SDL_GLContext _glContext;
		SDL_Window* _window;
	};

}