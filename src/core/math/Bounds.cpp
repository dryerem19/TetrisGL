#include "Bounds.h"

Bounds::Bounds()
	: _center(0.0f), _extents(0.0f) {
}

Bounds::Bounds(const glm::vec2& center, const glm::vec2& size)
{
	this->Initialize(center, size);
}

void Bounds::Initialize(const glm::vec2& center, const glm::vec2& size)
{
	_center = center;
	_extents = size * 0.5f;
}

bool Bounds::Intersects(const Bounds& other) const
{
	glm::vec2 min1 = this->GetMin();
	glm::vec2 max1 = this->GetMax();
	
	glm::vec2 min2 = other.GetMin();
	glm::vec2 max2 = other.GetMax();

	return (min1.x <= max2.x && max1.x >= min2.x &&
		min1.y <= max2.y && max1.y >= min2.y);
}

const glm::vec2& Bounds::GetCenter() const
{
	return _center;
}

const glm::vec2& Bounds::GetExtents() const
{
	return _extents;
}

glm::vec2 Bounds::GetSize() const
{
	return _extents * 2.0f;
}

glm::vec2 Bounds::GetMax() const
{
	return _center + _extents;
}

glm::vec2 Bounds::GetMin() const
{
	return _center - _extents;
}
