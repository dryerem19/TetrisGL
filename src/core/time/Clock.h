#pragma once

/**
* @brief ����� ��� ��������� �������.
*/
class Clock
{
public:

	/**
	* @brief �����������.
	* 
	* ��������� ����.
	*/
	Clock();

	/**
	* @brief ���������� �����, ��������� � ������� �����.
	* 
	* @return ������� � �������� ����� ������� �������� � �������� � ������� ������� �����. 
	*/
	double GetElapsedTime() const;

	/**
	* @brief ������������� ����
	*/
	void Restart();

protected:

	/**
	* ����� ������� �����.
	*/
	double _startTime;
};