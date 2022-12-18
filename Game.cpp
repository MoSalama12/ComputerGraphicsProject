#include "Game.h"

const int screenWidth = 800, screenHeight = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

bool Game::init()
{
	


	player = Player(glm::vec2(500.0f, 450.0f), 50.0f, 5.0f);
	food = Food(glm::vec2(700.0f, 350.0f), 300.0f);

	return true;
}

void Game::gameLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		renderer->Clear();
		sh->uniformMat4x4("projection", player.getCamera().constructProjectionMatrix());
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		//player.draw(renderer, sh);
		
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
}

void Game::terminate()
{
	sh->destroyShader();
	delete sh;
	glfwTerminate();
}

void Game::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		player.move(directions::UP);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		player.move(directions::DOWN);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		player.move(directions::LEFT);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		player.move(directions::RIGHT);
}
