#pragma once

#include <AL/al.h>
#include <AL/alc.h>

#include <iostream>
#include <vector>
#include <thread>

/* Forward declarations */
class AudioSource;

/**
 * @brief �����, ��������������� ��������������� OpenAL.
 *
 * @details ���� ����� ���������� ��� ��������, ����� ���������� ������ ����� �������
 * � ��������������� � ��������� OpenAL. ��� �����������, ��� ������ ���� ��������������� � ��������
 * OpenAL ����� ���������������� �� ����� ���������� ���������.
 */
class AudioDevice
{
public:

	/**
	 * @brief ����������� ����� ��� ��������� ���������� AudioDevice.
	 *
	 * @details ���������� ������������ ��������� AudioDevice. ��� ������ ������
	 *          ������ ���������� ������������� AudioDevice (��������������� � ��������).
	 *
	 * @return  ������ �� ��������� AudioDevice.
	 */
	static AudioDevice& GetInstance();

	const std::shared_ptr<AudioSource>& CreateSource();

	/**
	* @brief ��������� ��������� �����. 
	*/
	void Update();

	/*
	* @brief �������� ������ OpenAL.
	*/
	void PrintOpenALVersion();

private:

	/**
	* ���������� OpenAL.
	*/
	ALCdevice* _device{ nullptr };

	/**
	* @brief �������� OpenAL.
	*/
	ALCcontext* _context{ nullptr };

	/**
	* ��������� �����.
	*/
	std::vector<std::shared_ptr<AudioSource>> _sources;

	/**
	 * @brief ����������� �� ���������.
	 *
	 * @details �������������� ��������������� � �������� OpenAL.
	 */
	AudioDevice();

	/**
	 * @brief ����������.
	 *
	 * @details ����������� ������� OpenAL (�������� � ����������).
	 *
	 */
	~AudioDevice();

	/**
	 * @brief ��������� ����������� �������.
	 *
	 * @details ��� ���������� ��� ���������� ���������.
	 */
	AudioDevice(const AudioDevice&) = delete;

	/**
	 * @brief ��������� �������� ������������ ������������.
	 *
	 * @details ��� ���������� ��� ���������� ���������.
	 */
	AudioDevice& operator=(const AudioDevice&) = delete;
};