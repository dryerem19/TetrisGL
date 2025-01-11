#include "Camera.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera()
{
}

const glm::mat4& Camera::GetTopLeftProjection() const
{
	return _topLeftProjectionMatrix;
}

const glm::mat4& Camera::GetBottomLeftProjection() const
{
	return _bottomLeftProjectionMatrix;
}

void Camera::SetViewport(int x, int y, int width, int height)
{
	glViewport(x, y, width, height);

	_topLeftProjectionMatrix = glm::ortho(0.0f, float(width), float(height), 0.0f);
	_bottomLeftProjectionMatrix = glm::ortho(0.0f, float(width), 0.0f, float(height));
}