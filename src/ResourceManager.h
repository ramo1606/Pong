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
	static Texture2D* getSprite(EPONG_SPRITES obj);
	static Sound* getSound(EPONG_SOUNDS obj);
	static Music* getMusic(EPONG_MUSIC obj);
	void cleanup();

private:
	static ResourceManager* m_Instance;
	std::map<EPONG_SPRITES, Texture2D> m_SpritesMap;
	std::map<EPONG_SOUNDS, Sound> m_SoundsMap;
	std::map<EPONG_MUSIC, Music> m_MusicMap;
};