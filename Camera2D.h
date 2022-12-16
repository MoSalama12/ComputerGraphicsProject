#pragma once
#include "Dep/glm/glm.hpp"
#include "Dep/glm/gtc/matrix_transform.hpp"
#include <glad/glad.h>

extern const int screenWidth, screenHeight;

class Camera2D
{
public:
	Camera2D() = default;
	Camera2D(glm::vec2 focusPosition, float zoom);
	glm::mat4x4 constructProjectionMatrix();
	void setFocusPosition(glm::vec2 newFocus);
	glm::vec2 getFocusPosition();
	void zoomBy(float amount);
private:
	glm::vec2 focusPosition;
	float zoom;
};

