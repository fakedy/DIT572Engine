#pragma once
#include <glad/glad.h>
#include <iostream>
#include <SDL3/SDL.h>

namespace Engine {



	class Shader {
	public:

		Shader(const char* vertexPath, const char* fragmentPath) {
			
			void* vertexData = SDL_LoadFile(vertexPath, nullptr);
			void* fragmentData = SDL_LoadFile(fragmentPath, nullptr);
			vertexCode = std::string(static_cast<char*>(vertexData));
			fragmentCode = std::string(static_cast<char*>(fragmentData));

			SDL_free(vertexData);
			SDL_free(fragmentData);
		}
		void createShader() {

			int success;
			char log[512];

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

		int getLocation(const std::string& name) {
			return glGetUniformLocation(id, name.c_str());
		}

	private:

		std::string vertexCode;
		std::string fragmentCode;

		int id;

	};
}