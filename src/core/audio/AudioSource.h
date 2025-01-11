#pragma once
#include "AudioClip.h"

#include <mutex>

/**
* @brief �����, ������� ��������� ����������� �����.
*/
class AudioSource
{
public:

	/**
	* @brief ������� ��������� ������.
	*/
	AudioSource();

	/**
	* @brief �������� ��� ��������� ������������.
	* @param loop �������� ������������.
	*/
	void SetLoop(bool loop);

	/**
	* @brief ������������� ��������� ��������� ����� (�� 0.0 �� 1.0)
	* 
	* @param value ����� ������� ������� ��������� ����� 1, � ����� ������ � 0, ��� ������� ���� �� ������
	*/
	void SetVolume(float value);

	/**
	* @brief ������ ��������� ��� ����� ���������.
	* @param clip ���������, ������� ����� ���������.
	*/
	void SetClip(const std::shared_ptr<AudioClip>& clip);

	/**
	* @brief ������������� ����.
	*/
	void Play();

	/**
	* @brief ��������������� �� ����.
	*/
	bool IsPlaying() const;

	/*
	* @brief ����������� ��������� � ������������ ��������� � ������������ � volumeScale
	* 
	* @param clip ���������
	* @param volumeScale ����������� ��������� (0...1)
	*/
	void PlayOneShot(const std::shared_ptr<AudioClip>& clip, float volumeScale = 1.0f) const;

	/**
	* @brief ���������� ���������. 
	*/
	const std::shared_ptr<AudioClip>& GetClip() const;

	/*
	* @brief ����������� ������� ������� OpenAL.
	*/
	~AudioSource();

private:

	/**
	* @brief ������� ��� ����������� ������������������.
	*/
	std::mutex _mutex;

	/**
	* @brief �������� ����� �� ������� ������� OpenAL.
	*/
	ALuint _source{ 0 };

	/**
	* ������� �� ��������� ����.
	*/
	bool _loop{ false };

	/**
	* ��������� ��������� �����.
	*/
	float _volume{ 1.0f };

	/**
	* @brief ���������.
	*/
	std::shared_ptr<AudioClip> _clip;
};