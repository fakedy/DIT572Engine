#include <vector>
#include "Layer.h"

namespace Engine {

	class Core {
	public:



		Core();
		virtual ~Core();


		virtual void run();

		void addLayer(Layer* layer);

	private:

		bool running{ true };
		std::vector<Layer*> layers;
	};
}