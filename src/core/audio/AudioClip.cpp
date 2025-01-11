#include "AudioClip.h"

int AudioClip::GetFrequency() const
{
	return _frequency;
}

int AudioClip::GetChannels() const
{
	return _channels;
}

int AudioClip::GetSamples() const
{
	return _samples;
}

std::shared_ptr<AudioClip> AudioClip::Create(int samples, int channels, int frequency)
{
	auto clip = std::make_shared<AudioClip>();

	clip->_samples = samples;
	clip->_channels = channels;
	clip->_frequency = frequency;

	alGenBuffers(1, &clip->_buffer);

	ALenum err = alGetError();
	if (err != AL_NO_ERROR) {
		fprintf(stderr, "OpenAL Error: %s\n", alGetString(err));
		return nullptr;
	}

	return clip;
}

bool AudioClip::SetData(const std::vector<short>& data)
{
	if (data.empty() || !_buffer) {
		return false;
	}

	ALenum err = AL_NO_ERROR;

	alBufferData(_buffer, this->GetFormat(), data.data(), data.size() * sizeof(data[0]), _frequency);

	err = alGetError();	
	if (err != AL_NO_ERROR) {
		fprintf(stderr, "OpenAL Error: %s\n", alGetString(err));
		return false;
	}
}

AudioClip::~AudioClip()
{
	if (_buffer != 0) {
		alDeleteBuffers(1, &_buffer);
	}
}

ALenum AudioClip::GetFormat() const
{
	ALenum format = AL_NONE;

	if (_channels == 1) {
		format = AL_FORMAT_MONO16;
	}
	else if (_channels == 2) {
		format = AL_FORMAT_STEREO16;
	}

	return format;
}
