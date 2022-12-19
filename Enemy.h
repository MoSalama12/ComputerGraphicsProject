#pragma once
#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include <vector>
#include "Player.h"
#include "data.h"

class Enemy
{
public:
	Enemy(glm::vec2 center, float sideLength, std::string textureSource, Player* player);
	void draw(Renderer* renderer, Shader* shader);
	std::vector<float> updateVerticies();
	glm::vec2 getCenter() { return this->center; }
	float getSideLength() { return this->sideLength; }
	void setHasBeenEaten(bool eaten) { hasBeenEaten = eaten; }
	bool getIsEaten() { return this->hasBeenEaten; }
	void move();
private:
	glm::vec2 center;
	float sideLength;
	std::vector<std::pair<int, int>> path;
	bool hasBeenEaten;
	std::vector<float> verticies;
	Texture* texture;
	VertexBuffer* vb;
	VertexArray* va;
	IndexBuffer* ib;
	Player* m_player;
	std::string m_state;
	glm::vec2 m_walkCenter;
};

