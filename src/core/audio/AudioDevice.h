#pragma once

#include <AL/al.h>
#include <AL/alc.h>

#include <iostream>
#include <vector>
#include <thread>

/* Forward declarations */
class AudioSource;

/**
 * @brief Класс, инкапсулирующий аудиоустройство OpenAL.
 *
 * @details Этот класс реализован как синглтон, чтобы обеспечить единую точку доступа
 * к аудиоустройству и контексту OpenAL. Это гарантирует, что только одно аудиоустройство и контекст
 * OpenAL будут инициализированы во время выполнения программы.
 */
class AudioDevice
{
public:

	/**
	 * @brief Статический метод для получения экземпляра AudioDevice.
	 *
	 * @details Возвращает единственный экземпляр AudioDevice. При первом вызове
	 *          метода происходит инициализация AudioDevice (аудиоустройство и контекст).
	 *
	 * @return  Ссылка на экземпляр AudioDevice.
	 */
	static AudioDevice& GetInstance();

	const std::shared_ptr<AudioSource>& CreateSource();

	/**
	* @brief Обновляет источники звука. 
	*/
	void Update();

	/*
	* @brief Печатает версию OpenAL.
	*/
	void PrintOpenALVersion();

private:

	/**
	* Устройство OpenAL.
	*/
	ALCdevice* _device{ nullptr };

	/**
	* @brief Контекст OpenAL.
	*/
	ALCcontext* _context{ nullptr };

	/**
	* Источники звука.
	*/
	std::vector<std::shared_ptr<AudioSource>> _sources;

	/**
	 * @brief Конструктор по умолчанию.
	 *
	 * @details Инициализирует аудиоустройство и контекст OpenAL.
	 */
	AudioDevice();

	/**
	 * @brief Деструктор.
	 *
	 * @details Освобождает ресурсы OpenAL (контекст и устройство).
	 *
	 */
	~AudioDevice();

	/**
	 * @brief Запрещает копирование объекта.
	 *
	 * @details Это необходимо для реализации синглтона.
	 */
	AudioDevice(const AudioDevice&) = delete;

	/**
	 * @brief Запрещает оператор присваивания копированием.
	 *
	 * @details Это необходимо для реализации синглтона.
	 */
	AudioDevice& operator=(const AudioDevice&) = delete;
};