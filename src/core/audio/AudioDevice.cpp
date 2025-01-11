#include "AudioDevice.h"
#include "AudioSource.h"

#include <stdexcept>

AudioDevice& AudioDevice::GetInstance()
{
	static AudioDevice instance;
	return instance;
}

const std::shared_ptr<AudioSource>& AudioDevice::CreateSource()
{
	auto source = std::make_shared<AudioSource>();
	_sources.emplace_back(source);
	return _sources.back();
}

void AudioDevice::Update()
{
	for (auto it = _sources.begin(); it != _sources.end(); ) {
		auto& source = *it;

		if (!source->IsPlaying()) {
			it = _sources.erase(it);
		}
		else {
			it++;
		}
	}
}

void AudioDevice::PrintOpenALVersion()
{
	std::cout << "OpenAL Vendor: " << alGetString(AL_VENDOR) << std::endl;
	std::cout << "OpenAL Version: " << alGetString(AL_VERSION) << std::endl;
	std::cout << "OpenAL Renderer: " << alGetString(AL_RENDERER) << std::endl;
	std::cout << "OpenAl Extensions: " << alGetString(AL_EXTENSIONS) << std::endl;
	std::cout << "\n" << std::endl;
}

AudioDevice::AudioDevice()
{
	_device = alcOpenDevice(nullptr);
	if (!_device) {
		throw std::runtime_error("Couldn't open audio device.");
	}

	_context = alcCreateContext(_device, nullptr);
	if (!_context) {
		throw std::runtime_error("Couldn't create audio context.");
	}

	if (!alcMakeContextCurrent(_context)) {
		throw std::runtime_error("Couldn't select audio context.");
	}

	PrintOpenALVersion();
}

AudioDevice::~AudioDevice()
{
	_sources.clear();

	if (_context) {
		alcDestroyContext(_context);
		_context = nullptr;
	}

	if (_device) {
		alcCloseDevice(_device);
		_device = nullptr;
	}
}
