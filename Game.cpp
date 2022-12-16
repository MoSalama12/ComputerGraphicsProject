#include "Game.h"

const int screenWidth = 800, screenHeight = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

bool Game::init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	window = glfwCreateWindow(screenWidth, screenHeight, "test", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed To Create GLFW Window\n";
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);

	float vertices[] = {
		300.5f,  300.5f, 0.0f, 
		300.5f,  150.5f, 0.0f,  
		150.5f,  150.5f, 0.0f,  
		150.5f,  300.5f, 0.0f   
	};
	unsigned int indices[] = {  
		0, 1, 3,  
		1, 2, 3   
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	std::string VSPath = "C:\\Users\\PC\\source\\repos\\Project1\\Shaders\\SimpleVertexShader.vertexshader";
	std::string FSPath = "C:\\Users\\PC\\source\\repos\\Project1\\Shaders\\SimpleFragmentShader.fragmentshader";
	sh = Shader(VSPath, FSPath);
	sh.useShader();


	player = Player(glm::vec2(500.0f, 450.0f), 50.0f, 5.0f);
	food = Food(glm::vec2(700.0f, 350.0f), 300.0f);

	return true;
}

void Game::gameLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.1f, 0.4f, 1.0f, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		sh.uniformMat4x4("projection", player.getCamera().constructProjectionMatrix());
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		player.draw();
		food.draw();
		if (!food.hasBeenEaten())
		{
			food.collidingWithPlayer(player);
		}
		
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
}

void Game::terminate()
{
	sh.destroyShader();
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
