#pragma once
#include <glm/glm.hpp>

class Camera
{
protected:
	glm::mat4 _topLeftProjectionMatrix    = glm::mat4(1.0f);
	glm::mat4 _bottomLeftProjectionMatrix = glm::mat4(1.0f);

public:
	Camera();

	/**
	* @brief левостороннюю ортографическую проекцию с началом координат в левом верхнем углу.
	*/
	const glm::mat4& GetTopLeftProjection() const;

	/**
	* @brief Возвращает левостороннюю ортографическую проекцию с началом координат в левом нижнем углу.
	*/
	const glm::mat4& GetBottomLeftProjection() const;

	void SetViewport(int x, int y, int width, int height);
};