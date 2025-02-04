#pragma once

#include <glm/glm.hpp>

#include "Font.h"

/**
* @brief ���������� �������� ������ ��� ������������. 
* 
* ��� ����� ������������ ��� �������������� ��������, ��������� ���������� GUI ��� ������� ������.
*/
class Text
{
public:

	/**
	* @brief ������������� �����, ������� ����� ����������� ��� ������ ������.
	*/
	void SetFont(const std::shared_ptr<Font>& font);

	/**
	* @brief ������������� �����, ������� ����� ���������.
	* 
	* ���� �� ���������� �����, ����� ��������� "Lorem ipsum".
	*/
	void SetText(const std::string& text);

	/*
	* @brief ������������� ������ �������, � ������� ����� ��������� �����.
	* 
	* ��� ��������� ������ ����������� ����������� ����������� ������� ������� (������������� ���� ��������), 
	* �� ��������� � ������� �������, � ������� ��� �������� �����.
	* ����� �������, ����� ����� ������������ ������ ������� ��������.
	* 
	* @param size ������ �������, ������� ����� ����������. 
	*/
	void SetSize(int size);

	/*
	* @brief ������������� ����, � ������� ����� ��������� �����.
	*/
	void SetColor(const glm::vec4& color);

	/**
	* @brief ������������� ������� ������ �� ������.
	*/
	void SetPosition(const glm::ivec2& position);

	/**
	* @brief ���������� ������������� �����.
	*/
	const std::shared_ptr<Font>& GetFont() const;

	/**
	* @brief ���������� ������ ������.
	* 
	* �������� ����� ��������� ������ � ������� ������!
	*/
	int GetWidth() const;

	/*
	* @brief ���������� �������� ������ ������.
	* 
	* ����� ���� ������� � ���������, ����� �� ������ ���������� ����� �� ������ ������������ ���� ����.
	* �������� ����� ��������� ������ � ������� ������!
	*/
	int GetHalfWidth() const;

	/*
	* @brief ���������� ������ �������, ������� ����� ����������.
	*/
	int GetSize() const;

	/**
	* @brief ���������� ������� ������.
	*/
	const glm::ivec2& GetPosition() const;

	/*
	* @brief ���������� ����, � ������� ����� ��������� �����.
	*/
	const glm::vec4& GetColor() const;

	/*
	* @brief ���������� ������������� �����.
	*/
	const std::string& GetText() const;

protected:

	/**
	* @brief �����, ����������� ��� ������ ������. 
	*/
	std::shared_ptr<Font> _font;

	/**
	* @brief ���� ������, �� ��������� - �����.
	*/
	glm::vec4 _color{ 1.0f, 1.0f, 1.0f, 1.0f };

	/**
	* @brief ������� ������ �� ������.
	*/
	glm::ivec2 _position{ 100, 100 };

	/**
	* @brief ������ �������, � ������� ����� ���������� �����.
	*/
	int _size{ 14 };

	/**
	* @brief �����, ������� ����� ���������.
	*/
	std::string _text{ "Lorem ipsum" };
};