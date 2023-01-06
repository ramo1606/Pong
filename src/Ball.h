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

	EPONG_SOUNDS m_HitSounds[5] { EPONG_SOUNDS::HIT_0, EPONG_SOUNDS::HIT_1, EPONG_SOUNDS::HIT_2, EPONG_SOUNDS::HIT_3, EPONG_SOUNDS::HIT_4 };
	EPONG_SOUNDS m_BounceSounds[5]{ EPONG_SOUNDS::BOUNCE_0, EPONG_SOUNDS::BOUNCE_1, EPONG_SOUNDS::BOUNCE_2, EPONG_SOUNDS::BOUNCE_3, EPONG_SOUNDS::BOUNCE_4 };
};