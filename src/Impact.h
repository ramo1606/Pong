#pragma once
#include <vector>

#include "Actor.h"

class Impact : public Actor 
{
public:
	Impact(Vector2 pos = { 0, 0 });
	~Impact();

	void update() override;

	int getTime() { return m_Time; }

private:
	int m_Time{ 0 };
	std::vector<Texture2D*> m_Animations;
};