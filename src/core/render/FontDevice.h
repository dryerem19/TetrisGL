#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

/*
* @brief ����� ��������������� ���������� FreeType 
*/
class FontDevice
{
public:

	/**
	 * @brief ����������� ����� ��� ��������� ���������� FontDevice.
	 *
	 * @details ���������� ������������ ��������� FontDevice. ��� ������ ������
	 *          ������ ���������� �������������.
	 *
	 * @return  ������ �� ��������� FontDevice.
	 */
	static FontDevice& GetInstance();

	/**
	* @brief ���������� ��������� �� ���������� FreeType.
	*/
	FT_Library GetLibrary() const;

private:

	/*
	* @brief ���������� FreeType.
	*/
	FT_Library _library{ nullptr };

	/**
	 * @brief ����������� �� ���������.
	 */
	FontDevice();

	/**
	 * @brief ����������.
	 */
	~FontDevice();

	/**
	 * @brief ��������� ����������� �������.
	 *
	 * @details ��� ���������� ��� ���������� ���������.
	 */
	FontDevice(const FontDevice&) = delete;

	/**
	 * @brief ��������� �������� ������������ ������������.
	 *
	 * @details ��� ���������� ��� ���������� ���������.
	 */
	FontDevice& operator=(const FontDevice&) = delete;
};