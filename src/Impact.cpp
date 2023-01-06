#include "Impact.h"
#include "ResourceManager.h"

Impact::Impact(Vector2 pos) : Actor("", pos, nullptr)
{
	m_Animations.push_back(ResourceManager::getSprite(EPONG_SPRITES::IMPACT_0));
	m_Animations.push_back(ResourceManager::getSprite(EPONG_SPRITES::IMPACT_1));
	m_Animations.push_back(ResourceManager::getSprite(EPONG_SPRITES::IMPACT_2));
	m_Animations.push_back(ResourceManager::getSprite(EPONG_SPRITES::IMPACT_3));
	m_Animations.push_back(ResourceManager::getSprite(EPONG_SPRITES::IMPACT_4));
	m_Image = m_Animations[0];
}

Impact::~Impact()
{
	m_Animations.clear();
}

void Impact::update()
{
	if (m_Time < 10) 
	{
		m_Image = m_Animations[std::floorf(m_Time / 2)];
	}
	m_Time += 1;
}
