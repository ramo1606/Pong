#include "ResourceManager.h"

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
	m_SpritesMap.emplace(EPONG_SPRITES::MENU_0, LoadTexture(ASSETS_PATH"images/menu0.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::MENU_1, LoadTexture(ASSETS_PATH"images/menu1.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::GAME_OVER, LoadTexture(ASSETS_PATH"images/over.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::TABLE, LoadTexture(ASSETS_PATH"images/table.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::BALL, LoadTexture(ASSETS_PATH"images/ball.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::BAT_1, LoadTexture(ASSETS_PATH"images/bat00.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::BAT_1_LIGHT, LoadTexture(ASSETS_PATH"images/bat01.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::BAT_1_SHADOW, LoadTexture(ASSETS_PATH"images/bat02.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::BAT_2, LoadTexture(ASSETS_PATH"images/bat10.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::BAT_2_LIGHT, LoadTexture(ASSETS_PATH"images/bat11.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::BAT_2_SHADOW, LoadTexture(ASSETS_PATH"images/bat12.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::EFFECT_0, LoadTexture(ASSETS_PATH"images/effect0.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::EFFECT_1, LoadTexture(ASSETS_PATH"images/effect1.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::IMPACT_0, LoadTexture(ASSETS_PATH"images/impact0.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::IMPACT_1, LoadTexture(ASSETS_PATH"images/impact1.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::IMPACT_2, LoadTexture(ASSETS_PATH"images/impact2.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::IMPACT_3, LoadTexture(ASSETS_PATH"images/impact3.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::IMPACT_4, LoadTexture(ASSETS_PATH"images/impact4.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_0, LoadTexture(ASSETS_PATH"images/digit00.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_1, LoadTexture(ASSETS_PATH"images/digit01.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_2, LoadTexture(ASSETS_PATH"images/digit02.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_3, LoadTexture(ASSETS_PATH"images/digit03.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_4, LoadTexture(ASSETS_PATH"images/digit04.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_5, LoadTexture(ASSETS_PATH"images/digit05.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_6, LoadTexture(ASSETS_PATH"images/digit06.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_7, LoadTexture(ASSETS_PATH"images/digit07.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_8, LoadTexture(ASSETS_PATH"images/digit08.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_9, LoadTexture(ASSETS_PATH"images/digit09.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_PLAYER_1_0, LoadTexture(ASSETS_PATH"images/digit20.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_PLAYER_1_1, LoadTexture(ASSETS_PATH"images/digit21.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_PLAYER_1_2, LoadTexture(ASSETS_PATH"images/digit22.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_PLAYER_1_3, LoadTexture(ASSETS_PATH"images/digit23.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_PLAYER_1_4, LoadTexture(ASSETS_PATH"images/digit24.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_PLAYER_1_5, LoadTexture(ASSETS_PATH"images/digit25.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_PLAYER_1_6, LoadTexture(ASSETS_PATH"images/digit26.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_PLAYER_1_7, LoadTexture(ASSETS_PATH"images/digit27.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_PLAYER_1_8, LoadTexture(ASSETS_PATH"images/digit28.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_PLAYER_1_9, LoadTexture(ASSETS_PATH"images/digit29.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_PLAYER_2_0, LoadTexture(ASSETS_PATH"images/digit10.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_PLAYER_2_1, LoadTexture(ASSETS_PATH"images/digit11.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_PLAYER_2_2, LoadTexture(ASSETS_PATH"images/digit12.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_PLAYER_2_3, LoadTexture(ASSETS_PATH"images/digit13.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_PLAYER_2_4, LoadTexture(ASSETS_PATH"images/digit14.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_PLAYER_2_5, LoadTexture(ASSETS_PATH"images/digit15.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_PLAYER_2_6, LoadTexture(ASSETS_PATH"images/digit16.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_PLAYER_2_7, LoadTexture(ASSETS_PATH"images/digit17.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_PLAYER_2_8, LoadTexture(ASSETS_PATH"images/digit18.png"));
	m_SpritesMap.emplace(EPONG_SPRITES::SCORE_PLAYER_2_9, LoadTexture(ASSETS_PATH"images/digit19.png"));

	//Load Sounds
	m_SoundsMap.emplace(EPONG_SOUNDS::BOUNCE_SYNTH, LoadSound(ASSETS_PATH"sounds/bounce_synth0.ogg"));
	m_SoundsMap.emplace(EPONG_SOUNDS::BOUNCE_0, LoadSound(ASSETS_PATH"sounds/bounce0.ogg"));
	m_SoundsMap.emplace(EPONG_SOUNDS::BOUNCE_1, LoadSound(ASSETS_PATH"sounds/bounce1.ogg"));
	m_SoundsMap.emplace(EPONG_SOUNDS::BOUNCE_2, LoadSound(ASSETS_PATH"sounds/bounce2.ogg"));
	m_SoundsMap.emplace(EPONG_SOUNDS::BOUNCE_3, LoadSound(ASSETS_PATH"sounds/bounce3.ogg"));
	m_SoundsMap.emplace(EPONG_SOUNDS::BOUNCE_4, LoadSound(ASSETS_PATH"sounds/bounce4.ogg"));
	m_SoundsMap.emplace(EPONG_SOUNDS::DOWN, LoadSound(ASSETS_PATH"sounds/down.ogg"));
	m_SoundsMap.emplace(EPONG_SOUNDS::UP, LoadSound(ASSETS_PATH"sounds/up.ogg"));
	m_SoundsMap.emplace(EPONG_SOUNDS::HIT_SYNTH, LoadSound(ASSETS_PATH"sounds/hit_synth0.ogg"));
	m_SoundsMap.emplace(EPONG_SOUNDS::HIT_SLOW, LoadSound(ASSETS_PATH"sounds/hit_slow0.ogg"));
	m_SoundsMap.emplace(EPONG_SOUNDS::HIT_MEDIUM, LoadSound(ASSETS_PATH"sounds/hit_medium0.ogg"));
	m_SoundsMap.emplace(EPONG_SOUNDS::HIT_FAST, LoadSound(ASSETS_PATH"sounds/hit_fast0.ogg"));
	m_SoundsMap.emplace(EPONG_SOUNDS::HIT_VERY_FAST, LoadSound(ASSETS_PATH"sounds/hit_veryfast0.ogg"));
	m_SoundsMap.emplace(EPONG_SOUNDS::HIT_0, LoadSound(ASSETS_PATH"sounds/hit0.ogg"));
	m_SoundsMap.emplace(EPONG_SOUNDS::HIT_1, LoadSound(ASSETS_PATH"sounds/hit1.ogg"));
	m_SoundsMap.emplace(EPONG_SOUNDS::HIT_2, LoadSound(ASSETS_PATH"sounds/hit2.ogg"));
	m_SoundsMap.emplace(EPONG_SOUNDS::HIT_3, LoadSound(ASSETS_PATH"sounds/hit3.ogg"));
	m_SoundsMap.emplace(EPONG_SOUNDS::HIT_4, LoadSound(ASSETS_PATH"sounds/hit4.ogg"));
	m_SoundsMap.emplace(EPONG_SOUNDS::SCORE_GOAL, LoadSound(ASSETS_PATH"sounds/score_goal0.ogg"));

	//Load Music
	m_MusicMap.emplace(EPONG_MUSIC::THEME, LoadMusicStream(ASSETS_PATH"music/theme.ogg"));

	return true;
}

Texture2D* ResourceManager::getSprite(EPONG_SPRITES obj)
{
	auto& spritesMap = m_Instance->m_SpritesMap;
	auto it = spritesMap.find(obj);
	if (it == spritesMap.end()) {
		return nullptr;
	}
	return &(it->second);
}

Sound* ResourceManager::getSound(EPONG_SOUNDS obj)
{
	auto& soundsMap = m_Instance->m_SoundsMap;
	auto it = soundsMap.find(obj);
	if (it == soundsMap.end()) {
		return nullptr;
	}
	return &(it->second);
}

Music* ResourceManager::getMusic(EPONG_MUSIC obj)
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
