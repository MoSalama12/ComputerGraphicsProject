#pragma once
#include <vector>
#include <glad/glad.h>
#include "Camera2D.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "Renderer.h"
#include "Texture.h"

enum class directions
{
	UP, DOWN, LEFT, RIGHT
};

class Player
{
public:
	Player() = default;
	~Player();
	Player(glm::vec2 center, float sideLength, float speed);
	void draw(Renderer* renderer, Shader* shader);
	void move(directions direction);
	std::vector<float> updateVerticies();
	Camera2D getCamera();
	void updateZoom(float amount);
	VertexArray* getVertexArray();
	IndexBuffer* getIndexBuffer();

	glm::vec2 getCenter();
	float getSideLength();
private:
	float sideLength, speed;
	glm::vec2 center;
	std::vector<float> verticies;
	VertexArray* va;
	IndexBuffer* ib;
	VertexBuffer* vb;
	Texture* texture;

	Camera2D camera;
};

