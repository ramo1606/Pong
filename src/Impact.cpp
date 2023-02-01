#include "Impact.h"
#include "ResourceManager.h"

Impact::Impact(Vector2 pos) : Actor("", pos, nullptr)
{
	m_Image = ResourceManager::getSprite(std::string("impact0"));
}

void Impact::update()
{
	// There are 5 impact sprites numbered 0 to 4. We update to a new sprite every 2 frames.
	if (m_Time < 10) 
	{
		m_Image = ResourceManager::getSprite(std::string("impact") + std::to_string(m_Time / 2));
	}

	// The Game class maintains a list of Impact instances.In Game.update, if the timer for an object
	// has gone beyond 10, the object is removed from the list.
	m_Time += 1;
}