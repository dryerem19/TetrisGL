#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "../core/render/Renderer.h"

struct Tetramino
{
	int id;
	Sprite& tile;
	glm::ivec2 blocksPositions[4];
	glm::ivec2 prevBlocksPositions[4];

	Tetramino(Sprite& tile);
	void Draw(Renderer& renderer) const;
	void MoveDown();
	void MoveBack();
	void Rotate();
};