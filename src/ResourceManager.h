#pragma once
#include <memory>
#include <map>

#include "raylib.h"
#include "Common.h"

using namespace Common;

/*
* ResourceManager class will load all the images, sounds and music needed by the game and add it to a map, 
* so we can get each resource by it file name. This way we don't have to load the resource every time we needed, 
* we keep it in memory.
*/
class ResourceManager
{
public:
	~ResourceManager();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	static std::shared_ptr<ResourceManager> getInstance();
	bool loadResources();
	void cleanup();
	
	static Texture2D* getSprite(std::string& obj);
	static Sound* getSound(std::string& obj);
	static Music* getMusic(std::string& obj);

private:
	ResourceManager();
	static std::shared_ptr<ResourceManager> m_Instance;
	
	std::map<std::string, Texture2D> m_SpritesMap;
	std::map<std::string, Sound> m_SoundsMap;
	std::map<std::string, Music> m_MusicMap;
};