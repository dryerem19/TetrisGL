#include "AudioSource.h"
#include "AudioDevice.h"

AudioSource::AudioSource()
{
	// Генерация источника на стороне сервера OpenAL
	alGenSources(1, &_source);

	ALenum err = alGetError();
	if (err != AL_NO_ERROR) {
		fprintf(stderr, "OpenAL Error: could not create source: %s\n", alGetString(err));
		return;
	}

	alSourcef(_source, AL_PITCH, 1.0f);
	alSourcef(_source, AL_GAIN, 1.0f);
	alSource3f(_source, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSource3f(_source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	alSourcei(_source, AL_LOOPING, AL_FALSE);
}

void AudioSource::SetLoop(bool loop)
{
	_loop = loop;
	alSourcei(_source, AL_LOOPING, _loop);
}

void AudioSource::SetVolume(float value)
{
	_volume = value;
	alSourcef(_source, AL_GAIN, _volume);
}

void AudioSource::SetClip(const std::shared_ptr<AudioClip>& clip)
{
	_clip = clip;
}

void AudioSource::Play()
{
	alSourcei(_source, AL_BUFFER, (ALint)_clip->_buffer);
	alSourcePlay(_source);
}

bool AudioSource::IsPlaying() const
{
	ALint state = AL_PLAYING;
	alGetSourcei(_source, AL_SOURCE_STATE, &state);
	return state == AL_PLAYING;
}

void AudioSource::PlayOneShot(const std::shared_ptr<AudioClip>& clip, float volumeScale) const
{
	auto& source = AudioDevice::GetInstance().CreateSource();
	if (source->_source) {
		/* Привязка буфера к новому источнику */
		alSourcei(source->_source, AL_BUFFER, (ALint)clip->_buffer);

		/* Установка громкости */
		float volume = _volume * volumeScale;
		alSourcef(source->_source, AL_GAIN, volume);
	
		/* Воспроизведение */
		alSourcePlay(source->_source);
	}
}

const std::shared_ptr<AudioClip>& AudioSource::GetClip() const
{
	return _clip;
}

AudioSource::~AudioSource()
{
	if (_source != 0) {
		alDeleteSources(1, &_source);
	}
}
