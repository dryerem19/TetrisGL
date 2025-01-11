#pragma once

#include "Sprite.h"
#include "Camera.h"
#include "Text.h"

class Renderer
{
private:
	unsigned int _shaderProgram;
	unsigned int _VBO, _VAO, _EBO;
	unsigned int _uColorLocation = -1, _uTransformLocation = -1, _uProjectionLocation = -1;
	Camera* _camera;
public:
	static Renderer& GetInstance();
	void SetCamera(Camera* camera);
	void DrawSprite(const Sprite* sprite) const;

	/*
	* @brief Печатает текст на экране.
	*/
	void DrawText(const Text& text);

private:
	void PrepareShaders();
	void PrepareBuffers();

	Renderer();
	~Renderer();

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
};