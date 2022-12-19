#include "Enemy.h"
#include <queue>
#include <set>

Enemy::Enemy(glm::vec2 center, float sideLength, std::string textureSource, Player* player)
{
    this->m_player = player;
	this->center = center;
	this->sideLength = sideLength;
	this->hasBeenEaten = false;
    this->m_state = "Idle";
	texture = new Texture(textureSource);
    verticies = updateVerticies();
    unsigned int indicies[] = {
    0, 1, 3,
    1, 2, 3
    };
    vb = new VertexBuffer(&verticies[0], verticies.size() * sizeof(float));
    ib = new IndexBuffer(indicies, 6);
    va = new VertexArray();
    VertexBufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(2);
    va->AddBuffer(*vb, layout);
}

void Enemy::draw(Renderer* renderer, Shader* shader)
{
    texture->Bind(1);
    shader->setUniform1i(std::string("u_Texture"), 1);
    renderer->Draw(this->va, this->ib, shader, GL_TRIANGLES);
}

std::vector<float> Enemy::updateVerticies()
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

void Enemy::move()
{
    if (glm::distance(m_player->getCenter(), this->center) < 450.0f)
    {
        m_state = "Fight";
        glm::vec2 player_pos = m_player->getCenter();

        if (player_pos.x > this->center.x)
            this->center.x++;
        else
            this->center.x--;

        if (player_pos.y > this->center.y)
            this->center.y++;
        else
            this->center.y--;

        std::cout << this->center.x << ", " << this->center.y << "\n";
    }
    else {
        if (m_state == "Idle")
        {
            m_state = "Walking";
            int randomIndex = rand() % 99;
            this->m_walkCenter = glm::vec2(randomPosition[randomIndex][0], randomPosition[randomIndex][1]);
        }
        else if (m_state == "Walking") {
            if (this->m_walkCenter.x >= this->center.x)
                this->center.x += 2;
            else
                this->center.x -= 2;

            if (this->m_walkCenter.y >= this->center.y)
                this->center.y += 2;
            else
                this->center.y -= 2;

            if (glm::distance(m_walkCenter, this->center) < 100.0f)
            {
                m_state = "Idle";
            }
        }
        else if (m_state != "Fighting")
        {
            m_state = "Idle";
        }
    }

    this->verticies = this->updateVerticies();
    va->Bind();
    vb = new VertexBuffer(&verticies[0], verticies.size() * sizeof(float));
    VertexBufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(2);
    va->AddBuffer(*vb, layout);
}