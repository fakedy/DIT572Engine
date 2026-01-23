#include <Engine/Renderer.h>
#include <glm/glm/gtc/matrix_transform.hpp>


namespace Engine {


	int Renderer::init() {


		glGenBuffers(1, &VAO);
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


		return 0;
	}


	void Renderer::draw() {
		for (auto& pair : spriteMap) {
			pair.second->draw();
		}
	}

	void Renderer::drawSprite(glm::mat4 model)
	{
		defaultShader.use();
		glBindVertexArray(VAO);
		int projLoc = defaultShader.getLocation("proj");
		int modelLoc = defaultShader.getLocation("model");

		glm::mat4 proj = glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f, -1.0f, 1.0f);
		glm::mat4 tempModel = glm::scale(model, glm::vec3(100.0f, 100.0f, 1.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &tempModel[0][0]);
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, &proj[0][0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	}


	void Renderer::clear() {
		glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	int Renderer::addSprite(Sprite* sprite)
	{
		int id = nextSprite++;
		spriteMap[id] = sprite;
		return id;
	}

	void Renderer::removeSprite(int id)
	{
		
	}



}