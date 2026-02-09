#pragma once
#include <string>



namespace Engine {


	class Texture {
	public:

		Texture() {

		}
		~Texture() = default;

		std::string filepath;
		unsigned int id;
		unsigned int width;
		unsigned int height;

	};
}