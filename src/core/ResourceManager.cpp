#include "ResourceManager.h"

#include <functional> // std::function
#include <iostream>   // std::cout, std::endl
#include <vector>     // std::vector

#include <sndfile.h>

std::shared_ptr<AudioClip> ResourceManager::LoadAudioClip(const std::string& filename)
{
	/* Our audio container*/
	std::shared_ptr<AudioClip> clip;

	/* File information */
	SF_INFO sfinfo{ 0 };

	/**
	* Open the file and retrieve sample information.
	* 
	* We wrap it in unique_ptr to automatically close the file in case of an error and other unforeseen situations.
	*/	
	std::unique_ptr<SNDFILE, std::function<void(SNDFILE*)>> sndfile(
		sf_open(filename.c_str(), SFM_READ, &sfinfo),
		[&](SNDFILE* f) {
			if (f) {
				sf_close(f);
			}
		});

	if (!sndfile) {
		printf("Unable to open ’%s’.\n", filename.c_str());
		return { 0 };
	}

	if (sfinfo.frames < 1 || sfinfo.frames>(sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels) {
		std::cout << "Error: bad sample count in " << filename << std::endl;
	}

	if (sfinfo.channels < 1 || sfinfo.channels > 2) {
		std::cout << "Error: unsupported channel count. Audio file must be mono or stereo." << std::endl;
	}

	if (sfinfo.format == (SF_FORMAT_WAV | SF_FORMAT_PCM_16)) {
		std::vector<short> buffer(sfinfo.frames * sfinfo.channels);
		if (sf_readf_short(sndfile.get(), buffer.data(), sfinfo.frames) < 1) {
			std::cout << "Error: failed to read samples in" << filename << std::endl;
		}
		else {

			clip = AudioClip::Create(sfinfo.frames, sfinfo.channels, sfinfo.samplerate);
			clip->SetData(buffer);
		}
	}

	return clip;
}

ResourceManager& ResourceManager::GetInstance()
{
	static ResourceManager manager;
	return manager;
}

const std::shared_ptr<Texture>& ResourceManager::LoadTexture(const std::string& filename)
{
	auto texture = std::make_shared<Texture>();
	if (texture->LoadFromFile(filename)) {
		texture->Create();
		Textures[filename] = texture;
		return Textures[filename];
	}

	return { };
}

const std::shared_ptr<Texture>& ResourceManager::GetTexture(const std::string& name)
{
	return Textures[name];
}
