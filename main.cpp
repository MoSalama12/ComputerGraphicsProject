#include <iostream>
#include "Shader.h"
#include <GLFW/glfw3.h>
#include "Dep/glm/glm.hpp"
#include "Dep/glm/gtc/matrix_transform.hpp"
#include "Renderer.h"
#include "Texture.h"
#include "Player.h"
#include "Enemy.h"
#include "Food.h"
#include "data.h"


int main()
{
	srand(time(0));
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Renderer* renderer = new Renderer();

	GLFWwindow* window = glfwCreateWindow(800, 600, "test", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed To Create GLFW Window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	
	float vertices[] = {
		-3500.0f, 3500.0f, 0.0f, 0.0f, 
		 3500.0f, 3500.0f, 1.0f, 0.0f,
		 3500.0f,-3500.0f, 1.0f, 1.0f,
		-3500.0f,-3500.0f, 0.0f, 1.0f
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
	Player* player = new Player(glm::vec2(250.0f, 250.0f), 80.0f, 10.0f);

	int num_Food = 225;
	std::vector <Food*> food_pointer;
	for (int i = 0; i < num_Food; i++)
	{
		int randomIndex = rand() % 224;
		food_pointer.push_back(new Food(player, randomPosition[randomIndex][0], randomPosition[randomIndex][1]));
	}

	std::string VSPath = "Shaders\\SimpleVertexShader.vertexshader";
	std::string FSPath = "Shaders\\SimpleFragmentShader.fragmentshader";
	Shader* sh = new Shader(VSPath, FSPath);
	sh->useShader();
	
	glm::mat4 projectionMatrix = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
	Texture texture("red-grunge-background.png");
	vector<Enemy*> enemeyVector;
	for (int i = 0; i < 20; i++)
	{
		int randomIndex = rand() % 224;
		enemeyVector.push_back(new Enemy(glm::vec2(randomPosition[randomIndex][0], randomPosition[randomIndex][1]), std::max(rand() % 250, 50), "image-291309.png", player));
	}
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
		texture.Bind(2);
		sh->setUniform1i(std::string("u_Texture"), 2);
		renderer->Draw(va, ib, sh, GL_TRIANGLES);
		for (int i = 0; i < num_Food; i++)
		{
			
			if ((!food_pointer[i]->hasBeenEaten()) && player->inCollision(food_pointer[i]->getCenter(), food_pointer[i]->getSideLength(), "food"))
			{
				food_pointer[i]->setIsEaten(true);
			}
			if (!food_pointer[i]->hasBeenEaten())
				food_pointer[i]->draw(renderer, sh);
		}
			

		for (size_t i = 0; i < enemeyVector.size(); i++)
		{
			if ((!enemeyVector[i]->getIsEaten()) && player->inCollision(enemeyVector[i]->getCenter(), enemeyVector[i]->getSideLength(), "enemy") == 2)
			{
				sh->destroyShader();
				delete sh;
				delete player;
				glfwTerminate();
				return 0;
			}
			else if ((!enemeyVector[i]->getIsEaten()) && player->inCollision(enemeyVector[i]->getCenter(), enemeyVector[i]->getSideLength(), "enemy") == 3)
			{
				enemeyVector[i]->setHasBeenEaten(true);
			}
			if (!enemeyVector[i]->getIsEaten())
			{
				enemeyVector[i]->draw(renderer, sh);
				enemeyVector[i]->move();
			}
		}
		player->draw(renderer, sh);


		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	sh->destroyShader();
	delete sh;
	delete player;
	glfwTerminate();
	return 0;
}
