#pragma once
#include <iostream>
#include "Shader.h"
#include "Player.h"
#include "Camera2D.h"
#include <GLFW/glfw3.h>
#include "Dep/glm/glm.hpp"
#include "Dep/glm/gtc/matrix_transform.hpp"
#include "Food.h"
#include "Renderer.h"

class Game
{
public:
	Game() = default;
	bool init();
	void gameLoop();
	void terminate();
	void processInput(GLFWwindow* window);
private:
	GLFWwindow* window;
	Shader* sh;
	unsigned int VBO, VAO, EBO;
	Food food;
	Player player;
	Renderer* renderer;
};

