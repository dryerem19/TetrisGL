#pragma once

#include <map>    // std::map
#include <string> // std::string
#include <memory> // std::shared_ptr, std::unique_ptr
#include <vector> // std::vector

#include "Shader.h"
#include "Texture.h"
#include "FontDevice.h"

/**
* @brief Шрифт FreeType.
*/
class Font
{
public:

	/**
	* @brief Свойства загруженного символа.
	*/
	struct CharacterProperties
	{
		/* Код символа */
		unsigned int code;

		/* Эти свойства предоставляет библиотека FreeType  */
		int width;
		int height;
		int advanceX;
		int bearingX;
		int bearingY;

		/* Свойства, необходимые для отрисовки. */
		int renderIndex;
		int textureIndex;
	};

	/* Конструктор */
	Font();

	/**
	* @brief Создает шрифт с указанным размером.
	*
	* @param filename Путь к файлу шрифта на диске.
	* @param size Размер пикселя загруженных символов.
	*
	* @return Указатель на созданный шрифт.
	*
	* @warning Функция может вернуть 'nullptr', если произошла ошибка при создании шрифта.
	* Проверьте возвращаемый указатель перед использованием.
	*/
	static std::shared_ptr<Font> Create(const std::string& filename, int size);

	/**
	* @brief Проверяет наличие символа в шрифте.
	*/
	bool HasChar(unsigned char c);

	/**
	* @brief Возвращает параметры символа.
	* 
	* @param c Код символа.
	*/
	const CharacterProperties& GetProperties(unsigned char c) const;

	/**
	* @brief Проверяет, был ли загружен шрифт.
	*/
	bool IsLoaded() const;

	/** 
	* @brief Возвращает размер пикселя, с которым был загружен шрифт.
	*/
	int GetSize() const;

private:

	/**
	* @brief Делаем класс отрисовки дружественным, чтобы он мог получить доступ к VAO.
	*/
	friend class Renderer;

	/**
	* @brief Карта со свойствами каждого загруженного символа.
	*/
	std::map<int, CharacterProperties> _characterProperties;

	/**
	* @brief Вектор всех текстурных атласов.
	*/
	std::vector<std::unique_ptr<Texture>> _textures;

	/*
	* @brief Размер пикселя, с которым был загружен шрифт.
	*/
	int _size{ 0 };

	/**
	* @brief VAO для отрисовки символов.
	*/
	unsigned int _vao{ 0 };

	/**
	* @brief VBO для хранения данных вершин.
	*/
	unsigned int _vbo{ 0 };

	/**
	* @brief Шейдерная программа для отрисовки символов.
	*/
	Shader _shader;

	/**
	* @brief Расположение матрицы проекции в шейдере.
	*/
	unsigned int _projectionMatrixLocation{ 0 };

	/**
	* @brief Расположение матрицы модели в шейдере.
	*/
	unsigned int _modelMatrixLocation{ 0 };

	/**
	* @brief Расположение переменной цвета в шейдере.
	*/
	unsigned int _colorUniformLocation{ 0 };

	/**
	* @brief Был ли шрифт загружен успешно.
	*/
	bool _loaded{ false };
	
	/**
	* @brief Эта константа определяет размер одного текстурного атласа.
	*/
	static const int CHARACTERS_TEXTURE_SIZE;
};