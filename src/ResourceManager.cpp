#include "ResourceManager.h"
#include "Utilities.h"

std::shared_ptr<ResourceManager> ResourceManager::m_Instance = nullptr;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

std::shared_ptr<ResourceManager> ResourceManager::getInstance()
{
	if (!m_Instance)
		m_Instance.reset(new ResourceManager());
	return m_Instance;
}

bool ResourceManager::loadResources()
{
	//Load sprites in images folder and 
	std::string images_folder = ASSETS_PATH"images/";
	auto images = Utils::GetFileList(images_folder);
	for (const auto& image : images)
	{
		auto pos = image.first.find(".png");
		m_SpritesMap.emplace(image.first.substr(0, pos), LoadTexture((images_folder + image.first).c_str()));
	}

	//Load Sounds
	std::string sounds_folder = ASSETS_PATH"sounds/";
	auto sounds = Utils::GetFileList(sounds_folder);
	for (const auto& sound : sounds)
	{
		auto pos = sound.first.find(".ogg");
		m_SoundsMap.emplace(sound.first.substr(0, pos), LoadSound((sounds_folder + sound.first).c_str()));
	}

	//Load Music
	std::string music_folder = ASSETS_PATH"music/";
	auto music = Utils::GetFileList(music_folder);
	for (const auto& theme : music)
	{
		auto pos = theme.first.find(".ogg");
		m_MusicMap.emplace(theme.first.substr(0, pos), LoadMusicStream((music_folder + theme.first).c_str()));
	}

	return true;
}

Texture2D* ResourceManager::getSprite(std::string& obj)
{
	//Search the image in the map and return it, return nullptr if image does not exists
	auto& spritesMap = m_Instance->m_SpritesMap;
	auto it = spritesMap.find(obj);
	if (it == spritesMap.end()) {
		return nullptr;
	}
	return &(it->second);
}

Sound* ResourceManager::getSound(std::string& obj)
{
	//Search the sound in the map and return it, return nullptr if image does not exists
	auto& soundsMap = m_Instance->m_SoundsMap;
	auto it = soundsMap.find(obj);
	if (it == soundsMap.end()) {
		return nullptr;
	}
	return &(it->second);
}

Music* ResourceManager::getMusic(std::string& obj)
{
	//Search the music in the map and return it, return nullptr if image does not exists
	auto& musciMap = m_Instance->m_MusicMap;
	auto it = musciMap.find(obj);
	if (it == musciMap.end()) {
		return nullptr;
	}
	return &(it->second);
}

void ResourceManager::cleanup()
{
	//Unload resources and clear maps.
	auto& spritesMap = m_Instance->m_SpritesMap;
	for (auto& sprite : spritesMap) 
	{
		UnloadTexture(sprite.second);
	}
	spritesMap.clear();

	auto& soundsMap = m_Instance->m_SoundsMap;
	for (auto& sound : soundsMap)
	{
		UnloadSound(sound.second);
	}
	soundsMap.clear();

	auto& musicMap = m_Instance->m_MusicMap;
	for (auto& music : musicMap)
	{
		UnloadMusicStream(music.second);
	}
	musicMap.clear();
}
