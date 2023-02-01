#include "Actor.h"

Actor::Actor(std::string name, Vector2 pos, Texture2D* image)
	: m_Name(name),
	  m_Pos(pos),
	  m_Image(image)
{
}

void Actor::setImage(Texture2D& image)
{
	m_Image = &image;
}

void Actor::processInput()
{
}

void Actor::update()
{
}

void Actor::draw()
{
	//Call Raylib function to print this image.
	DrawTexture(*m_Image, m_Pos.x - m_Image->width/2, m_Pos.y - m_Image->height / 2, WHITE);
}

Vector2 Actor::getPosition() const
{
	return m_Pos;
}
