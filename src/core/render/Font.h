#pragma once

#include <map>    // std::map
#include <string> // std::string
#include <memory> // std::shared_ptr, std::unique_ptr
#include <vector> // std::vector

#include "Shader.h"
#include "Texture.h"
#include "FontDevice.h"

/**
* @brief ����� FreeType.
*/
class Font
{
public:

	/**
	* @brief �������� ������������ �������.
	*/
	struct CharacterProperties
	{
		/* ��� ������� */
		unsigned int code;

		/* ��� �������� ������������� ���������� FreeType  */
		int width;
		int height;
		int advanceX;
		int bearingX;
		int bearingY;

		/* ��������, ����������� ��� ���������. */
		int renderIndex;
		int textureIndex;
	};

	/* ����������� */
	Font();

	/**
	* @brief ������� ����� � ��������� ��������.
	*
	* @param filename ���� � ����� ������ �� �����.
	* @param size ������ ������� ����������� ��������.
	*
	* @return ��������� �� ��������� �����.
	*
	* @warning ������� ����� ������� 'nullptr', ���� ��������� ������ ��� �������� ������.
	* ��������� ������������ ��������� ����� ��������������.
	*/
	static std::shared_ptr<Font> Create(const std::string& filename, int size);

	/**
	* @brief ��������� ������� ������� � ������.
	*/
	bool HasChar(unsigned char c);

	/**
	* @brief ���������� ��������� �������.
	* 
	* @param c ��� �������.
	*/
	const CharacterProperties& GetProperties(unsigned char c) const;

	/**
	* @brief ���������, ��� �� �������� �����.
	*/
	bool IsLoaded() const;

	/** 
	* @brief ���������� ������ �������, � ������� ��� �������� �����.
	*/
	int GetSize() const;

private:

	/**
	* @brief ������ ����� ��������� �������������, ����� �� ��� �������� ������ � VAO.
	*/
	friend class Renderer;

	/**
	* @brief ����� �� ���������� ������� ������������ �������.
	*/
	std::map<int, CharacterProperties> _characterProperties;

	/**
	* @brief ������ ���� ���������� �������.
	*/
	std::vector<std::unique_ptr<Texture>> _textures;

	/*
	* @brief ������ �������, � ������� ��� �������� �����.
	*/
	int _size{ 0 };

	/**
	* @brief VAO ��� ��������� ��������.
	*/
	unsigned int _vao{ 0 };

	/**
	* @brief VBO ��� �������� ������ ������.
	*/
	unsigned int _vbo{ 0 };

	/**
	* @brief ��������� ��������� ��� ��������� ��������.
	*/
	Shader _shader;

	/**
	* @brief ������������ ������� �������� � �������.
	*/
	unsigned int _projectionMatrixLocation{ 0 };

	/**
	* @brief ������������ ������� ������ � �������.
	*/
	unsigned int _modelMatrixLocation{ 0 };

	/**
	* @brief ������������ ���������� ����� � �������.
	*/
	unsigned int _colorUniformLocation{ 0 };

	/**
	* @brief ��� �� ����� �������� �������.
	*/
	bool _loaded{ false };
	
	/**
	* @brief ��� ��������� ���������� ������ ������ ����������� ������.
	*/
	static const int CHARACTERS_TEXTURE_SIZE;
};