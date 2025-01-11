#include "direction.h"

// Unlike usual screen coordinates the positive y-axis points in the up-direction and the (0,0) coordinates are at the center of the graph, instead of top-left.

const glm::vec2 MOVE_DIRECTIONS[4] = {
	{ 0.0f,  1.0f }, // Up
	{ 0.0f, -1.0f }, // Down
	{ -1.0f, 0.0f }, // Left
	{ 1.0f,  0.0f }  // Right
};