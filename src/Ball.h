#pragma once
#include "Actor.h"
#include "Common.h"

using namespace Common;

class Game;

class Ball : public Actor 
{
public:
	Ball(Game& game, float dx);
	Ball(const Ball&) = default;
	Ball& operator=(const Ball&) = default;

	void update();
	void reset(int direction);

	bool out();

private:
	Game* m_Game = nullptr;
	float m_Dx{ 0.f };
	float m_Dy{ 0.f };

	int m_Speed{ 0 };
};