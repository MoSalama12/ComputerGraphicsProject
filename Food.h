#pragma once
#include <cmath>
#include <vector>
#include "Dep/include/glad/glad.h"
#include "Dep/glm/glm.hpp"
#include "Dep/glm/gtc/matrix_transform.hpp"
#include "Player.h"
#include <iostream>

class Food
{
public:
	Food() = default;
	Food(glm::vec2 pos, float sideLength);
	bool collidingWithPlayer(Player& player);
	bool hasBeenEaten();
	void draw();
private:
	void calculateVertices();
	float sideLength;
	glm::vec2 pos;
	std::vector<float> vertices;
	unsigned int VBO, VAO;
	bool isEaten;
};

