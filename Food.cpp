#include "Food.h"

Food::Food(glm::vec2 pos, float sideLength)
{
	this->isEaten = false;
	this->pos = pos;
	this->sideLength = sideLength;
	calculateVertices();
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_DYNAMIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

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
	/*
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
	*/
}

bool Food::hasBeenEaten()
{
	return this->isEaten;
}

void Food::draw()
{
	if (!isEaten)
	{
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}
}

void Food::calculateVertices()
{
	/*
	      A
		 / \
		/   \
	   /  c  \
	  B_______C

	  c is the center of the triangle given by the (x, y) coordinates in the constructor
	*/
	// calculate the coordiantes of the vertex at the top (vertex A)
	vertices.push_back(this->pos.x); // x coordinate of vertex A
	vertices.push_back(this->pos.y - ((float)sqrt(3) / 2.0f) * sideLength); // y coordiante of vertex A
	vertices.push_back(0);
	//calculate the coordiantes of the vertex at the top (vertex C)
	vertices.push_back(this->pos.x + (sideLength / 2.0f)); // x coordinate of vertex C
	vertices.push_back(this->pos.y - ((float)sqrt(3) / 6.0f) * sideLength); // y coordiante of vertex C
	vertices.push_back(0);
	//calculate the coordiantes of the vertex at the top (vertex B)
	vertices.push_back(this->pos.x - (sideLength / 2.0f)); // x coordinate of vertex B
	vertices.push_back(this->pos.y - ((float)sqrt(3) / 6.0f) * sideLength); // y coordiante of vertex B
	vertices.push_back(0);
}
