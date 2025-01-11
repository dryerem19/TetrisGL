#include "Sprite.h"

#include <glm/gtc/matrix_transform.hpp>

Sprite::Sprite(const std::shared_ptr<Texture>& texture)
	: _texture(texture) { }

void Sprite::SetTexture(const std::shared_ptr<Texture>& texture)
{
	_texture = texture;
}

void Sprite::SetPosition(const glm::vec2& position)
{
	_position = position;
	UpdateBounds();
}

void Sprite::SetSize(const glm::vec2& size)
{
	_size = size;
	UpdateBounds();
}

void Sprite::SetRotation(float rotation)
{
	_rotation = rotation;
}

const Bounds& Sprite::GetBounds() const
{
	return _bounds;
}

const Texture* Sprite::GetTexture() const
{
	return _texture.get();
}

const glm::vec2& Sprite::GetPosition() const
{
	return _position;
}

const glm::vec2& Sprite::GetSize() const
{
	return _size;
}

const float Sprite::GetRotation() const
{
	return _rotation;
}

glm::mat4 Sprite::GetMatrix() const
{
	// Make sure to initialize matrix to identity matrix first
	glm::mat4 transform = glm::mat4(1.0f);

	// Set a position of the sprite
	transform = glm::translate(transform, glm::vec3(_position, 0.0f));

	// Set a size of the sprite
	transform = glm::scale(transform, glm::vec3(_size, 0.0f));

	return transform;
}

void Sprite::UpdateBounds()
{
	_bounds.Initialize(_position + _size * 0.5f, _size);
}
