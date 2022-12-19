#include "Food.h"

Food::Food(Player * player , int x, int y)
{
	m_player = player;
	this->center = glm::vec2(x, y);
	this->sideLength = 40;
	unsigned int indicies[] = {
		0, 1, 3,
		1, 2, 3
	};
	verticies = this->updateVerticies();
	va = new VertexArray();
	ib = new IndexBuffer(indicies, 6);
	vb = new VertexBuffer(&verticies[0], verticies.size() * sizeof(float));
	VertexBufferLayout layout;
	layout.push<float>(2);
	layout.push<float>(2);
	va->AddBuffer(*vb, layout);
	texture = new Texture("food.png");
}

bool Food::hasBeenEaten()
{
	return this->isEaten;
}

void Food::draw(Renderer* renderer, Shader* shader)
{
	if (!isEaten)
	{
		texture->Bind();
		shader->setUniform1i(std::string("u_Texture"),0);
		renderer->Draw(this->va, this->ib, shader, GL_TRIANGLES);
	}
}

std::vector<float> Food::updateVerticies()
{
	/*
	calculate te square's 4 verticies(A, B, C, D) using the center point(c) and sideLength(s)

		A_______________B
		|               |
		|               |
		|       c       |s
		|               |
		|_______________|
		C               D
	*/
	std::vector<float> result;
	// Calculate C                        
	result.push_back(this->center.x - (this->sideLength / 2.0f)); // X pos
	result.push_back(this->center.y + (this->sideLength / 2.0f)); // Y pos  
	result.push_back(0.0f); // tex coordinate
	result.push_back(0.0f); // tex coordinate
	// Calculate D                       
	result.push_back(this->center.x + (this->sideLength / 2.0f)); // X pos
	result.push_back(this->center.y + (this->sideLength / 2.0f)); // Y pos
	result.push_back(1.0f); // tex coordinate
	result.push_back(0.0f); // tex coordinate
	// Calculate B                       
	result.push_back(this->center.x + (this->sideLength / 2.0f)); // X pos
	result.push_back(this->center.y - (this->sideLength / 2.0f)); // Y pos
	result.push_back(1.0f); // tex coordinate
	result.push_back(1.0f); // tex coordinate
	// Calculate A
	result.push_back(this->center.x - (this->sideLength / 2.0f)); // X pos
	result.push_back(this->center.y - (this->sideLength / 2.0f)); // Y pos   
	result.push_back(0.0f); // tex coordinate
	result.push_back(1.0f); // tex coordinate
	return result;
}
