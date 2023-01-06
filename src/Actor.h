#pragma once
#include <string>
#include <raylib.h>

class Actor 
{
public:
	Actor(std::string name = "", Vector2 pos = { 0, 0 }, Texture2D* image = nullptr);
	Actor(const Actor&) = default;
	Actor& operator=(const Actor&) = default;

	virtual void setImage(Texture2D& image);
	virtual void processInput();
	virtual void update();
	virtual void draw();

	Vector2 getPosition();

protected:
	std::string m_Name{ "" };
	Texture2D* m_Image = nullptr;
	Vector2 m_Pos{0, 0};
};