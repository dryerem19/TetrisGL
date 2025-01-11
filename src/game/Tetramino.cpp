#include "Tetramino.h"
#include "Settings.h"

Tetramino::Tetramino(Sprite& tile) 
	: tile(tile) 
{
	for (int i = 0; i < 4; ++i) {
		blocksPositions[i] = { 0, 0 };
		prevBlocksPositions[i] = { 0, 0 };
	}

	id = 0;
}

void Tetramino::Draw(Renderer& renderer) const
{
	for (int i = 0; i < 4; ++i) {
		tile.SetPosition({ blocksPositions[i].x * CELL_SIZE, blocksPositions[i].y * CELL_SIZE });
		renderer.DrawSprite(&tile);
	}
}

void Tetramino::MoveDown()
{
	for (int i = 0; i < 4; ++i) {
		prevBlocksPositions[i] = blocksPositions[i];
		blocksPositions[i].y += 1;
	}
}

void Tetramino::MoveBack()
{
	for (int i = 0; i < 4; ++i) {
		blocksPositions[i] = prevBlocksPositions[i];
	}
}

void Tetramino::Rotate()
{
	glm::ivec2 p = blocksPositions[1];
	for (int i = 0; i < 4; ++i) {
		int x = blocksPositions[i].y - p.y;
		int y = blocksPositions[i].x - p.x;

		blocksPositions[i].x = p.x - x;
		blocksPositions[i].y = p.y + y;
	}
}
