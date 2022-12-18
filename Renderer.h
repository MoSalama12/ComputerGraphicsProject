#pragma once
#include "Dep/include/glad/glad.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Dep/glm/glm.hpp"

using namespace std;

class Renderer
{
public:
	Renderer();
	Renderer(glm::vec4 clearColor);
	void updateClearColor(glm::vec4 clearColor);
	void Clear() const;
	void Draw(VertexArray *va, IndexBuffer *ib, Shader *shader, GLenum mode) const;
private:
	glm::vec4 m_ClearColor;
};

