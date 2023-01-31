#include "ResourceManager.h"
#include "Utilities.h"

ResourceManager* ResourceManager::m_Instance = nullptr;

ResourceManager::ResourceManager()
{
	if(!m_Instance)
		m_Instance = this;
}

ResourceManager::~ResourceManager()
{
}

bool ResourceManager::loadResources()
{
	//Load sprites
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
	auto& spritesMap = m_Instance->m_SpritesMap;
	auto it = spritesMap.find(obj);
	if (it == spritesMap.end()) {
		return nullptr;
	}
	return &(it->second);
}

Sound* ResourceManager::getSound(std::string& obj)
{
	auto& soundsMap = m_Instance->m_SoundsMap;
	auto it = soundsMap.find(obj);
	if (it == soundsMap.end()) {
		return nullptr;
	}
	return &(it->second);
}

Music* ResourceManager::getMusic(std::string& obj)
{
	auto& musciMap = m_Instance->m_MusicMap;
	auto it = musciMap.find(obj);
	if (it == musciMap.end()) {
		return nullptr;
	}
	return &(it->second);
}

void ResourceManager::cleanup()
{
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
