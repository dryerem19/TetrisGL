#pragma once

#include <memory> // std::shared_ptr
#include <vector> // std::vector

#include <AL/al.h>

/*
* @brief ��������� ��� �����������.
*/
class AudioClip
{
public:

	/**
	 * @brief ���������� ������� ������������� ����������.
	 *
	 * @return ������� ������������� � ������.
	 */
	int GetFrequency() const;

	/**
	 * @brief ���������� ���������� ������� � ����������.
	 *
	 * @return ���������� ������� (��������, 1 ��� ����, 2 ��� ������).
	 */
	int GetChannels() const;

	/**
	 * @brief ���������� ����� ���������� ������� ����������� � ����������.
	 *
	 * @return ���������� �������.
	 */
	int GetSamples() const;

	/**
	* @brief ������� ��������� � �������� ������� � �������, ������� � �������.
	* 
	* @param samples ���������� ���������� ������.
	* @param channels ���������� ������� �� ����.
	* @param frequency ������� ������� �����.
	* 
	* @return ��������� �� ��������� ���������. 
	* 
	* @warning ������� ����� ������� 'nullptr', ���� ��������� ������ ��� �������� ����������.
	* ��������� ������������ ��������� ����� �������������� ����������.
	*/
	static std::shared_ptr<AudioClip> Create(int samples, int channels, int frequency);

	/*
	* @brief ������������� ���������� ������ ����������.
	* @return ���� �� ������ ����������� ���������. 
	*/
	bool SetData(const std::vector<short>& data);

	/**
	* 
	* @brief ����������� �������.
	*/
	~AudioClip();

private:

	ALuint _buffer{ 0 };

	/**
	* @brief ���������� ������� � ����������.
	*/
	int _channels{ 0 };

	/**
	* @brief ������� ������������� ���������� � ������.
	*/
	int _frequency{ 0 };

	/**
	* @brief ����� ���������� � �������.
	*/
	int _samples{ 0 };

	/*
	* @brief ���������� ������ ����������.
	*/
	ALenum GetFormat() const;

	/**
	* @brief /ref AudioSource ������������� �����, ����� �� ��� �������� ������ � ����� ����� ������.
	*/
	friend class AudioSource;
};