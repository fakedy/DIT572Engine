#pragma once
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

namespace Engine {



	class Shader {
	public:

		Shader(const char* vertexPath, const char* fragmentPath) {

			int success;
			char log[512];
			
			std::ifstream vertexFile;
			std::ifstream fragmentFile;


			vertexFile.open(vertexPath);
			fragmentFile.open(fragmentPath);

			std::string vertexCode;
			std::string fragmentCode;

			std::stringstream vertexStream, fragmentStream;

			vertexStream << vertexFile.rdbuf();
			fragmentStream << fragmentFile.rdbuf();

			vertexCode = vertexStream.str();
			fragmentCode = fragmentStream.str();

			vertexFile.close();
			fragmentFile.close();

			unsigned int vertex, fragment;

			vertex = glCreateShader(GL_VERTEX_SHADER);
			fragment = glCreateShader(GL_FRAGMENT_SHADER);

			const char* vShaderCode = vertexCode.c_str();
			const char* fShaderCode = fragmentCode.c_str();

			glShaderSource(vertex, 1, &vShaderCode, NULL);
			glShaderSource(fragment, 1, &fShaderCode, NULL);

			glCompileShader(vertex);

			// fragment compile error check
			glGetProgramiv(id, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(id, 512, NULL, log);
				std::cout << "VERTEX COMPILATION FAIL: " << log << std::endl;
			}

			glCompileShader(fragment);

			// fragment compile error check
			glGetProgramiv(id, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(id, 512, NULL, log);
				std::cout << "FRAGMENT COMPILATION FAIL: " << log << std::endl;
			}

			id = glCreateProgram();

			glAttachShader(id, vertex);
			glAttachShader(id, fragment);
			glLinkProgram(id);

			glGetProgramiv(id, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(id, 512, NULL, log);
				std::cout << "SHADER LINK FAIL" << log << std::endl;
			}


			glDeleteShader(vertex);
			glDeleteShader(fragment);

		}
		
		void use() {
			glUseProgram(id);
		}

	private:

		int id;

	};
}