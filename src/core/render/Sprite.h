#pragma once
#include <memory>
#include <glm/glm.hpp>

#include "../math/Bounds.h"
#include "Texture.h"

class Sprite
{
private:
	std::shared_ptr<Texture> _texture;
	glm::vec2 _position = { 0.0f, 0.0f };
	glm::vec2 _size = { 1.0f, 1.0f };
	float _rotation = 0.0f;

	Bounds _bounds;
public:
	Sprite() = default;
	Sprite(const std::shared_ptr<Texture>& texture);

	void SetTexture(const std::shared_ptr<Texture>& texture);
	void SetPosition(const glm::vec2& position);
	void SetSize(const glm::vec2& size);
	void SetRotation(float rotation);

	const Bounds& GetBounds() const;
	const Texture* GetTexture() const;
	const glm::vec2& GetPosition() const;
	const glm::vec2& GetSize() const;
	const float GetRotation() const;
	glm::mat4 GetMatrix() const;

private:
	void UpdateBounds();
};