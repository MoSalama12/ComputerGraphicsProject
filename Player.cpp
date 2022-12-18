#include "Player.h"

Player::Player(glm::vec2 center, float sideLength, float speed)
{
    this->center = center;
    this->sideLength = sideLength;
    this->speed = speed;
    unsigned int indicies[] = {
        0, 1, 3,
        1, 2, 3
    };
    this->verticies = std::vector<float>(16);

    verticies = this->updateVerticies();
    va = new VertexArray();
    ib = new IndexBuffer(indicies, 6);
    camera = Camera2D(center, 1.0f);
    vb = new VertexBuffer(&verticies[0], verticies.size() * sizeof(float));
    VertexBufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(2);
    va->AddBuffer(*vb, layout);
    texture = new Texture("pngegg.png");

}
Player::~Player()
{
    delete va;
    delete vb;
    delete ib;
}

void Player::draw(Renderer* renderer, Shader* shader)
{
    texture->Bind();
    renderer->Draw(this->va, this->ib, shader, GL_TRIANGLES);
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
    this->verticies = this->updateVerticies();
    va->Bind();
    vb = new VertexBuffer(&verticies[0], verticies.size() * sizeof(float));
    VertexBufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(2);
    va->AddBuffer(*vb, layout);
    camera.setFocusPosition(center);
}

std::vector<float> Player::updateVerticies()
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

Camera2D Player::getCamera()
{
    return this->camera;
}

void Player::updateZoom(float amount)
{
    camera.zoomBy(amount);
}

VertexArray* Player::getVertexArray()
{
    return this->va;
}

IndexBuffer* Player::getIndexBuffer()
{
    return this-> ib;
}

glm::vec2 Player::getCenter()
{
    return this->center;
}

float Player::getSideLength()
{
    return this->sideLength;
}
