#include "Player.h"

Player::Player(glm::vec2 center, float radius, float speed)
{
    this->center = center;
    this->radius = radius;
    this->speed = speed;
    this->verticies = updateVerticies();
    camera = Camera2D(center, 1.0f);
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(float), &verticies[0], GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Player::draw()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, verticies.size() / 3);
    glBindVertexArray(0);
}

void Player::move(directions direction)
{
    switch (direction)
    {
    case directions::UP:
        this->center.y -= speed;
        break;
    case directions::DOWN:
        this->center.y += speed;
        break;
    case directions::LEFT:
        this->center.x -= speed;
        break;
    case directions::RIGHT:
        this->center.x += speed;
        break;
    }
    verticies = updateVerticies();
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(float), &verticies[0], GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    camera.setFocusPosition(center);
}

std::vector<float> Player::updateVerticies()
{
    std::vector<float> points;
    int numOfTriangles = 360;
    const float pi = 3.14159265f;
    for (int i = 0; i < numOfTriangles + 1; i++)
    {
        float theta = (float)((float)i / numOfTriangles * 2 * pi);
        points.push_back((float)(this->center.x + radius * cos(theta)));
        points.push_back((float)(this->center.y + radius * sin(theta)));
        points.push_back(0);
    }

    return points;
}

Camera2D Player::getCamera()
{
    return this->camera;
}

void Player::updateZoom(float amount)
{
    camera.zoomBy(amount);
}

glm::vec2 Player::getCenter()
{
    return this->center;
}

float Player::getRadius()
{
    return this->radius;
}
