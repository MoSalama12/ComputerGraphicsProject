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
	Food(Player * player , int x , int y);
	bool hasBeenEaten();
	void draw(Renderer* renderer, Shader* shader);
	std::vector<float> updateVerticies();
	glm::vec2 getCenter() { return this->center; }
	float getSideLength() { return this->sideLength; }
	void setIsEaten(bool eaten) { isEaten = eaten; }
private:
	float sideLength;
	glm::vec2 center;
	std::vector<float> verticies;
	bool isEaten;
	VertexArray* va;
	IndexBuffer* ib;
	VertexBuffer* vb;
	Texture* texture;
	Player* m_player;
};

