#pragma once
#include <vector>
#include <glad/glad.h>
#include "Camera2D.h"
#include <GLFW/glfw3.h>
#include <cmath>

enum class directions
{
	UP, DOWN, LEFT, RIGHT
};

class Player
{
public:
	Player() = default;
	Player(glm::vec2 center, float radius, float speed);
	void draw();
	void move(directions direction);
	std::vector<float> updateVerticies();
	Camera2D getCamera();
	void updateZoom(float amount);
	glm::vec2 getCenter();
	float getRadius();
private:
	float radius, speed;
	glm::vec2 center;
	std::vector<float> verticies;
	unsigned int VBO, VAO;
	Camera2D camera;
};

