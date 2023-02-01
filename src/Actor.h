#pragma once
#include <string>
#include <raylib.h>

/*
* Base Actor class, all the elements in the game will derive from this class.
* It contains the position and a pointer to a image that will draw every frame.
*/
class Actor 
{
public:
	Actor(std::string name = "Actor", Vector2 pos = { 0, 0 }, Texture2D* image = nullptr);
	Actor(const Actor&) = default;
	Actor& operator=(const Actor&) = default;
	~Actor() = default;

	virtual void update();
	virtual void draw();
	virtual void processInput();
	
	void setImage(Texture2D& image);
	Vector2 getPosition() const;

protected:
	std::string m_Name{ "Actor" };
	Texture2D* m_Image = nullptr;
	Vector2 m_Pos{0, 0};
};