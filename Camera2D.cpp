#include "Camera2D.h"

Camera2D::Camera2D(glm::vec2 focusPosition, float zoom)
{
	this->focusPosition = focusPosition;
	this->zoom = zoom;
}

glm::mat4x4 Camera2D::constructProjectionMatrix()
{
	GLint m_viewport[4];

	glGetIntegerv(GL_VIEWPORT, m_viewport);

	float left = focusPosition.x - m_viewport[2] / 2.0f;
	float right = focusPosition.x + m_viewport[2] / 2.0f;
	float bottom = focusPosition.y + m_viewport[3] / 2.0f;
	float top = focusPosition.y - m_viewport[3] / 2.0f;

	glm::mat4x4 orthoMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	glm::mat4x4 zoomMatrix = glm::mat4x4(1.0f) * zoom;
	return orthoMatrix * zoomMatrix;
}

glm::vec2 Camera2D::getFocusPosition()
{
	return this->focusPosition;
}

void Camera2D::zoomBy(float amount)
{
	this->zoom += amount;
}

void Camera2D::setFocusPosition(glm::vec2 newFocus)
{
	this->focusPosition = newFocus;
}
