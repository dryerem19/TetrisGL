#pragma once
#include <glm/glm.hpp>

class Bounds
{
protected:
	glm::vec2 _extents;
	glm::vec2 _center;
public:
	Bounds();
	Bounds(const glm::vec2& center, const glm::vec2& size);
	
	void Initialize(const glm::vec2& center, const glm::vec2& size);
	bool Intersects(const Bounds& other) const;

	const glm::vec2& GetCenter() const;
	const glm::vec2& GetExtents() const;

	glm::vec2 GetSize() const;
	glm::vec2 GetMax() const;
	glm::vec2 GetMin() const;
};