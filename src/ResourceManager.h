#pragma once
#include <memory>
#include <map>

#include "raylib.h"
#include "Common.h"

using namespace Common;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	bool loadResources();
	static Texture2D* getSprite(std::string& obj);
	static Sound* getSound(std::string& obj);
	static Music* getMusic(std::string& obj);
	void cleanup();

private:
	static ResourceManager* m_Instance;
	std::map<std::string, Texture2D> m_SpritesMap;
	std::map<std::string, Sound> m_SoundsMap;
	std::map<std::string, Music> m_MusicMap;
};