#pragma once
#include <string>
#include <glad/glad.h>

enum class WrapMode
{
	Repeat = GL_REPEAT,
	MirroredRepeat = GL_MIRRORED_REPEAT,
	ClampToEdge = GL_CLAMP_TO_EDGE,
	ClampToBorder = GL_CLAMP_TO_BORDER
};

enum class TextureFormat
{
	RGBA = GL_RGBA,
	DepthFormat = GL_DEPTH_COMPONENT
};

class Texture
{
private:
	bool _created;
	unsigned int _id;
	std::string _filepath;
	unsigned char* _buffer;
	int _width, _height, _channels;

	TextureFormat _format{ TextureFormat::RGBA };
	WrapMode _wrapMode;
public:
	Texture();
	~Texture();

	bool LoadFromFile(const std::string& filepath);
	bool LoadFromData(const unsigned char* data, int width, int height);
	bool Create();
	void Destroy();

	void SetWrapMode(WrapMode wrapMode);

	/*
	* @brief Устанавливает формат этого объекта текстуры.
	* 
	* @param format Формат текстуры.
	*/
	void SetFormat(TextureFormat format);

	/**
	* @brief Возвращает формат этого объекта текстуры.
	*/
	TextureFormat Format() const;

	void Bind(unsigned int slot = 0) const;
	static void Unbind();

	int Width() const;
	int Height() const;
	
	unsigned int TextureId() const;
	bool IsCreated() const;
};