#include <Engine/Renderer.h>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <Engine/Texture.h>

namespace Engine {
	Renderer::Renderer()
	{
		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
			SDL_Log("Failed to initialize GLAD");
		}

		defaultShader.createShader();
	}

	int Renderer::init() {


		glEnable(GL_DEPTH_TEST);

		// this should all be in like a Mesh::Quad or something
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
		glEnableVertexAttribArray(1);

		// this should be related to what camera is used, several cameras should be able to be used at once

		float aspectRatio = (float)windowWidth / (float)windowHeight;


		float orthoHeight = unitHeight / 2.0f;
		float orthoWidth = orthoHeight * aspectRatio;

		proj = glm::ortho(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, -1.0f, 1.0f);


		return 0;
	}


	void Renderer::draw() {
		for (auto& pair : RenderObjects) {

			pair.second->draw();
		}
	}

	void Renderer::drawSprite(glm::mat4 model, Material& material)
	{
		defaultShader.use();
		glBindVertexArray(VAO);
		int projLoc = defaultShader.getLocation("proj");
		int modelLoc = defaultShader.getLocation("model");

		float sizeX = (float)material.texture->width / pixels_per_unit;
		float sizeY = (float)material.texture->height / pixels_per_unit;

		glm::mat4 tempModel = glm::scale(model, glm::vec3(sizeX, sizeY, 1.0f));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, material.texture->id);

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &tempModel[0][0]);
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, &proj[0][0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	}


	void Renderer::clear() {
		glClearColor(0.45f, 0.9f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	int Renderer::addRenderObject(RenderComponent* sprite)
	{
		int id = nextRenderObject++;
		RenderObjects[id] = sprite;
		return id;
	}

	void Renderer::removeSprite(int id)
	{
		RenderObjects.erase(id);
	}

	void Renderer::handleResizeWindow(unsigned int width, unsigned int height) 
	{
		windowHeight = height;
		windowWidth = width;
		glViewport(0, 0, width, height);
	}

	void Renderer::drawLines(glm::mat4 model, glm::vec3 color) {
		defaultShader.use();
		glBindVertexArray(VAO);

		int projLoc = defaultShader.getLocation("proj");
		int modelLoc = defaultShader.getLocation("model");
		int colorLoc = defaultShader.getLocation("color");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, &proj[0][0]);
		glUniform3fv(colorLoc, 1, &color[0]);

		glBindVertexArray(VAO);
		glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, 0);
	}



}