#include "Food.h"

Food::Food(Player * player)
{
	glm::vec2 playerCenter = player->getCenter();
	this->center = glm::vec2(playerCenter.x+5, playerCenter.y+5);
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
/*
bool Food::collidingWithPlayer(Player& player)
{
	// player colliding with vertex
	float c1x = player.getCenter().x - this->vertices[0];
	float c1y = player.getCenter().y - this->vertices[1];
	float c2x = player.getCenter().x - this->vertices[3];
	float c2y = player.getCenter().y - this->vertices[4];
	float c3x = player.getCenter().x - this->vertices[6];
	float c3y = player.getCenter().y - this->vertices[7];


	if ((pow(c1x, 2) + pow(c1y, 2) <= pow(player.getRadius(), 2)) ||
		(pow(c2x, 2) + pow(c2y, 2) <= pow(player.getRadius(), 2)) ||
		(pow(c3x, 2) + pow(c3y, 2) <= pow(player.getRadius(), 2))
		)
	{
		isEaten = true;
		return true;
	}

	// player colliding with sides
	float edge1x = this->vertices[3] - this->vertices[0];
	float edge1y = this->vertices[4] - this->vertices[1];
	float edge2x = this->vertices[6] - this->vertices[3];
	float edge2y = this->vertices[7] - this->vertices[4];
	float edge3x = this->vertices[0] - this->vertices[6];
	float edge3y = this->vertices[1] - this->vertices[7];
	// first edge
	float dot = edge1x * c1x + edge1y * c1y;
	if (dot > 0)
	{
		float length = pow(edge1x, 2) + pow(edge1y, 2);
		dot = pow(dot, 2) / length;
		if (dot < length)
		{
			if ((pow(c1x, 2) + pow(c1y, 2)) - dot <= length)
			{
				isEaten = true;
				return true;
			}
		}
	}

	// second edge
	dot = edge2x * c2x + edge2y * c2y;
	if (dot > 0)
	{
		float length = pow(edge2x, 2) + pow(edge2y, 2);
		dot = pow(dot, 2) / length;
		if (dot < length)
		{
			if ((pow(c2x, 2) + pow(c2y, 2)) - dot <= length)
			{
				isEaten = true;
				return true;
			}
		}
	}

	// third edge
	dot = edge3x * c3x + edge3y * c3y;
	if (dot > 0)
	{
		float length = pow(edge3x, 2) + pow(edge3y, 2);
		dot = pow(dot, 2) / length;
		if (dot < length)
		{
			if ((pow(c3x, 2) + pow(c3y, 2)) - dot <= length)
			{
				isEaten = true;
				return true;
			}
		}
	}
	return false;
	
}*/

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
