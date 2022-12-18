#include <iostream>
#include "Shader.h"
#include <GLFW/glfw3.h>
#include "Dep/glm/glm.hpp"
#include "Dep/glm/gtc/matrix_transform.hpp"
#include "Renderer.h"
#include "Texture.h"
#include "Player.h"
#include "Food.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Renderer* renderer = new Renderer(glm::vec4(0.1f, 0.4f, 1.0f, 1.0f));

	GLFWwindow* window = glfwCreateWindow(800, 600, "test", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed To Create GLFW Window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	float vertices[] = {
		 450.0f, 350.0f, 0.0f, 0.0f, 
		 550.0f, 350.0f, 1.0f, 0.0f,
		 550.0f, 250.0f, 1.0f, 1.0f,
		 450.0f, 250.0f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};


	VertexBuffer* vb = new VertexBuffer(vertices, 4 * 4 * sizeof(float));
	VertexBufferLayout layout;
	layout.push<float>(2);
	layout.push<float>(2);
	IndexBuffer* ib = new IndexBuffer(indices, 6);
	VertexArray* va = new VertexArray();
	va->AddBuffer(*vb, layout);
	

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Player* player = new Player(glm::vec2(250.0f, 250.0f), 100.0f, 10.0f);
	
	int num_Food = 30;
	std::vector <Food*> food_pointer ;
	for (int i = 0; i < num_Food; i++)
		food_pointer.push_back(new Food(player));

	std::string VSPath = "Shaders\\SimpleVertexShader.vertexshader";
	std::string FSPath = "Shaders\\SimpleFragmentShader.fragmentshader";
	Shader* sh = new Shader(VSPath, FSPath);
	sh->useShader();
	Texture texture("pngegg.png");
	texture.Bind();
	sh->setUniform1i(std::string("u_Texture"), 0);
	glm::mat4 projectionMatrix = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

	while (!glfwWindowShouldClose(window))
	{
		sh->setUniformMat4f("u_MVP", player->getCamera().constructProjectionMatrix());
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			player->move(directions::UP);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			player->move(directions::DOWN);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			player->move(directions::LEFT);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			player->move(directions::RIGHT);
		renderer->Clear();

		player->draw(renderer, sh);
		for (int i = 0; i < num_Food; i++)
			food_pointer[i]->draw(renderer, sh); 
		renderer->Draw(va, ib, sh, GL_TRIANGLES);


		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	sh->destroyShader();
	delete sh;
	delete player;
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
