#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

/*
* @brief Класс инкапсулирующий библиотеку FreeType 
*/
class FontDevice
{
public:

	/**
	 * @brief Статический метод для получения экземпляра FontDevice.
	 *
	 * @details Возвращает единственный экземпляр FontDevice. При первом вызове
	 *          метода происходит инициализация.
	 *
	 * @return  Ссылка на экземпляр FontDevice.
	 */
	static FontDevice& GetInstance();

	/**
	* @brief Возвращает указатель на библиотеку FreeType.
	*/
	FT_Library GetLibrary() const;

private:

	/*
	* @brief Библиотека FreeType.
	*/
	FT_Library _library{ nullptr };

	/**
	 * @brief Конструктор по умолчанию.
	 */
	FontDevice();

	/**
	 * @brief Деструктор.
	 */
	~FontDevice();

	/**
	 * @brief Запрещает копирование объекта.
	 *
	 * @details Это необходимо для реализации синглтона.
	 */
	FontDevice(const FontDevice&) = delete;

	/**
	 * @brief Запрещает оператор присваивания копированием.
	 *
	 * @details Это необходимо для реализации синглтона.
	 */
	FontDevice& operator=(const FontDevice&) = delete;
};