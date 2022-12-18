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
	Food(Player player);
	bool collidingWithPlayer(Player& player);
	bool hasBeenEaten();
	void draw(Renderer* renderer, Shader* shader);
	std::vector<float> updateVerticies();
private:
	float sideLength;
	glm::vec2 center;
	std::vector<float> verticies;
	bool isEaten;
	VertexArray* va;
	IndexBuffer* ib;
	VertexBuffer* vb;
	Texture* texture;
};

