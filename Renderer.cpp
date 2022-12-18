#include "Renderer.h"
#include <iostream>

Renderer::Renderer()
{
	this->m_ClearColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

Renderer::Renderer(glm::vec4 clearColor)
{
	this->m_ClearColor = clearColor;
}

void Renderer::updateClearColor(glm::vec4 clearColor)
{
	this->m_ClearColor = clearColor;
}

void Renderer::Clear() const
{
	glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(VertexArray * va, IndexBuffer * ib, Shader * shader, GLenum mode) const
{
	shader->useShader();
	va->Bind();
	ib->Bind();
	
	glDrawElements(mode, ib->GetCount(), GL_UNSIGNED_INT, NULL);
}