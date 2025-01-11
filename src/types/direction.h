#pragma once
#include <glm/glm.hpp>

enum class Direction : uint8_t
{
	Up,
	Down,
	Left,
	Right
};

extern const glm::vec2 MOVE_DIRECTIONS[4];