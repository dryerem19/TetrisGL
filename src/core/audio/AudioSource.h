#pragma once
#include "AudioClip.h"

#include <mutex>

/**
* @brief Класс, который позволяет производить звуки.
*/
class AudioSource
{
public:

	/**
	* @brief Создает экземпляр класса.
	*/
	AudioSource();

	/**
	* @brief Включает или выключает зацикливание.
	* @param loop Параметр зацикливания.
	*/
	void SetLoop(bool loop);

	/**
	* @brief Устанавливает громкость источника звука (от 0.0 до 1.0)
	* 
	* @param value Самый высокий уровень громкости равен 1, а самый низкий — 0, при котором звук не слышен
	*/
	void SetVolume(float value);

	/**
	* @brief Задает аудиоклип для этого источника.
	* @param clip Аудиоклип, который нужно проиграть.
	*/
	void SetClip(const std::shared_ptr<AudioClip>& clip);

	/**
	* @brief Воспроизводит звук.
	*/
	void Play();

	/**
	* @brief Воспроизводится ли клип.
	*/
	bool IsPlaying() const;

	/*
	* @brief Проигрывает аудиоклип и масштабирует громкость в соответствии с volumeScale
	* 
	* @param clip Аудиоклип
	* @param volumeScale Коэффициент громкости (0...1)
	*/
	void PlayOneShot(const std::shared_ptr<AudioClip>& clip, float volumeScale = 1.0f) const;

	/**
	* @brief Возвращает аудиоклип. 
	*/
	const std::shared_ptr<AudioClip>& GetClip() const;

	/*
	* @brief Освобождает ресурсы сервера OpenAL.
	*/
	~AudioSource();

private:

	/**
	* @brief Мьютекс для обеспечения потокобезопасности.
	*/
	std::mutex _mutex;

	/**
	* @brief Источник звука на стороне сервера OpenAL.
	*/
	ALuint _source{ 0 };

	/**
	* Следует ли зациклить звук.
	*/
	bool _loop{ false };

	/**
	* Громкость источника звука.
	*/
	float _volume{ 1.0f };

	/**
	* @brief Аудиоклип.
	*/
	std::shared_ptr<AudioClip> _clip;
};