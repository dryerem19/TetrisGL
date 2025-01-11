#pragma once

#include <memory> // std::shared_ptr
#include <vector> // std::vector

#include <AL/al.h>

/*
* @brief Контейнер для аудиоданных.
*/
class AudioClip
{
public:

	/**
	 * @brief Возвращает частоту дискретизации аудиоклипа.
	 *
	 * @return Частота дискретизации в герцах.
	 */
	int GetFrequency() const;

	/**
	 * @brief Возвращает количество каналов в аудиоклипе.
	 *
	 * @return Количество каналов (например, 1 для моно, 2 для стерео).
	 */
	int GetChannels() const;

	/**
	 * @brief Возвращает общее количество выборок аудиоданных в аудиоклипе.
	 *
	 * @return Количество выборок.
	 */
	int GetSamples() const;

	/**
	* @brief Создает аудиоклип с заданной длинной в семплах, каналах и частоте.
	* 
	* @param samples Количество выборочных кадров.
	* @param channels Количество каналов на кадр.
	* @param frequency Частота выборки клипа.
	* 
	* @return Указатель на созданный аудиоклип. 
	* 
	* @warning Функция может вернуть 'nullptr', если произошла ошибка при создании аудиоклипа.
	* Проверьте возвращаемый указатель перед использованием аудиоклипа.
	*/
	static std::shared_ptr<AudioClip> Create(int samples, int channels, int frequency);

	/*
	* @brief Устанавливает выборочные данные аудиоклипа.
	* @return Были ли данные установлены корректно. 
	*/
	bool SetData(const std::vector<short>& data);

	/**
	* 
	* @brief Освобождает ресурсы.
	*/
	~AudioClip();

private:

	ALuint _buffer{ 0 };

	/**
	* @brief Количество каналов в аудиоклипе.
	*/
	int _channels{ 0 };

	/**
	* @brief Частота дискретизации аудиоклипа в герцах.
	*/
	int _frequency{ 0 };

	/**
	* @brief Длина аудиоклипа в сэмплах.
	*/
	int _samples{ 0 };

	/*
	* @brief Возвращает формат аудиоклипа.
	*/
	ALenum GetFormat() const;

	/**
	* @brief /ref AudioSource дружественный класс, чтобы он мог получить доступ к полям этого класса.
	*/
	friend class AudioSource;
};