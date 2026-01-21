#pragma once
#include <glad/glad.h>
#include <iostream>
#include <fstream>

namespace Engine {



	class Shader {
	public:

		Shader(const char* vertexPath, const char* fragmentPath) {

			
			std::ifstream vertexFile;
			std::ifstream fragmentFile;

			vertexFile.open(vertexPath);
			fragmentFile.open(fragmentPath);

			
			


		}
		



		int id;


	private:


	};
}