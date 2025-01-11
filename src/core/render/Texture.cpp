#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture()
	: _created(false), _id(0), _filepath(), _buffer(nullptr),
	_width(0), _height(0), _channels(0), _wrapMode(WrapMode::Repeat) { }

Texture::~Texture()
{
	Destroy();
}

bool Texture::LoadFromFile(const std::string& filepath)
{
	stbi_set_flip_vertically_on_load(true);
	_buffer = stbi_load(filepath.c_str(), &_width, &_height, &_channels, 4);

	if (_buffer) {
		_filepath = filepath;
		return true;
	}

	return false;
}

bool Texture::LoadFromData(const unsigned char* data, int width, int height)
{
	if (!_buffer) {

		_width = width;
		_height = height;

		auto size = static_cast<size_t>(_width) * _height;

		_buffer = new unsigned char[size];
		std::memcpy(_buffer, data, size);

		return true;
	}

	return false;
}

bool Texture::Create()
{
	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(_wrapMode));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(_wrapMode));

	glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(_format), _width, _height, 0, static_cast<GLint>(_format), GL_UNSIGNED_BYTE, _buffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenerateMipmap(GL_TEXTURE_2D);

	if (_buffer) 
	{
		/* Это просто вызов free(), так что это подходит и для сырового удаления */
		stbi_image_free(_buffer);
		_buffer = nullptr;

		if (_id > 0) {
			_created = true;
		}
	}
	
	return _created;
}

void Texture::Destroy()
{
	if (_buffer) {
		stbi_image_free(_buffer);
		_buffer = nullptr;
	}

	if (_id > 0) {
		glDeleteTextures(1, &_id);
		_id = 0;
	}

	_width = 0;
	_height = 0;
	_channels = 0;

	_filepath.clear();
	_created = false;
}

void Texture::SetWrapMode(WrapMode wrapMode)
{
	_wrapMode = wrapMode;
}

void Texture::SetFormat(TextureFormat format)
{
	_format = format;
}

TextureFormat Texture::Format() const
{
	return _format;
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::Width() const
{
	return _width;
}

int Texture::Height() const
{
	return _height;
}

unsigned int Texture::TextureId() const
{
	return _id;
}

bool Texture::IsCreated() const
{
	return _created;
}
