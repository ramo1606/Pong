#pragma once
#include <string>
#include <raylib.h>

class Actor 
{
public:
	Actor(std::string name = "Actor", Vector2 pos = { 0, 0 }, Texture2D* image = nullptr);
	Actor(const Actor&) = default;
	Actor& operator=(const Actor&) = default;
	~Actor() = default;

	//
	virtual void update();
	virtual void draw();
	
	//
	virtual void processInput();
	virtual void setImage(Texture2D& image);

	//
	Vector2 getPosition() const;

protected:
	std::string m_Name{ "Actor" };
	Texture2D* m_Image = nullptr;
	Vector2 m_Pos{0, 0};
};