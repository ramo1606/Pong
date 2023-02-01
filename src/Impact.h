#pragma once
#include <vector>

#include "Actor.h"

class Impact : public Actor 
{
public:
	Impact(Vector2 pos = { 0, 0 });
	Impact(const Impact&) = default;
	Impact& operator=(const Impact&) = default;
	~Impact() = default;

	void update() override;

	int getTime() const { return m_Time; }

private:
	int m_Time{ 0 };
};