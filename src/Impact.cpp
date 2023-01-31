#include "Impact.h"
#include "ResourceManager.h"

Impact::Impact(Vector2 pos) : Actor("", pos, nullptr)
{
	m_Image = ResourceManager::getSprite(std::string("impact0"));
}

Impact::~Impact()
{
}

void Impact::update()
{
	if (m_Time < 10) 
	{
		m_Image = ResourceManager::getSprite(std::string("impact") + std::to_string(m_Time / 2));
	}
	m_Time += 1;
}
