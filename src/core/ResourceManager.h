#pragma once

#include <memory>
#include <string>
#include <map>

#include "render/Texture.h"
#include "audio/AudioClip.h"

class ResourceManager
{
public:
	std::map<std::string, std::shared_ptr<Texture>> Textures;

	std::shared_ptr<AudioClip> LoadAudioClip(const std::string& filename);

	static ResourceManager& GetInstance();
	const std::shared_ptr<Texture>& LoadTexture(const std::string& filename);
	const std::shared_ptr<Texture>& GetTexture(const std::string& name);
private:
	ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
};