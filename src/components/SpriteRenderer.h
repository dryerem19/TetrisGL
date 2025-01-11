#pragma once
#include <inttypes.h>
#include <memory>

#include "../core/Sprite.h"

enum class SpriteDrawMode
{
	Normal,
	Tiled
};

struct SpriteRenderer
{
	std::shared_ptr<Sprite> sprite;
	std::uint32_t tileCountHeight;
	std::uint32_t tileCountWidth;
	SpriteDrawMode drawMode;
};