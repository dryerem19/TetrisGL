#pragma once

/**
* @brief Класс для измерения времени.
*/
class Clock
{
public:

	/**
	* @brief Конструктор.
	* 
	* Запускает часы.
	*/
	Clock();

	/**
	* @brief Возвращает время, прошедшее с запуска часов.
	* 
	* @return Разница в секундах между текущим временем и временем с момента запуска часов. 
	*/
	double GetElapsedTime() const;

	/**
	* @brief Перезапускает часы
	*/
	void Restart();

protected:

	/**
	* Время запуска часов.
	*/
	double _startTime;
};