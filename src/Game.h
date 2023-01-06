#pragma once
#include <vector>
#include <memory>

#include "Impact.h"
#include "Bat.h"
#include "Ball.h"

class Game 
{
public:
	Game(int players);

	void update();
	void draw();

	void reset(int players);
	void playSound(EPONG_SOUNDS sound, bool isMenu = false);
	void printScores();

	Ball& getBall();
	std::vector<std::unique_ptr<Bat>>& getBats();
	std::vector<std::unique_ptr<Impact>>& getImpacts();

	float getAIOffset() { return m_AI_Offset; }
	void setAIOffset(float value) { m_AI_Offset = value; }

private:
	void createPlayers(int players);
	std::vector<std::unique_ptr<Impact>> m_Impacts;
	std::vector<std::unique_ptr<Bat>> m_Bats;

	Ball m_Ball{ *this, -1.f };
	float m_AI_Offset{ 0.f };

	EPONG_SPRITES m_GreyNum[10]{ EPONG_SPRITES::SCORE_0, EPONG_SPRITES::SCORE_1, EPONG_SPRITES::SCORE_2, EPONG_SPRITES::SCORE_3, EPONG_SPRITES::SCORE_4, EPONG_SPRITES::SCORE_5, EPONG_SPRITES::SCORE_6, EPONG_SPRITES::SCORE_7, EPONG_SPRITES::SCORE_8, EPONG_SPRITES::SCORE_9 };
	EPONG_SPRITES m_Player1Num[10]{ EPONG_SPRITES::SCORE_PLAYER_1_0, EPONG_SPRITES::SCORE_PLAYER_1_1, EPONG_SPRITES::SCORE_PLAYER_1_2, EPONG_SPRITES::SCORE_PLAYER_1_3, EPONG_SPRITES::SCORE_PLAYER_1_4, EPONG_SPRITES::SCORE_PLAYER_1_5, EPONG_SPRITES::SCORE_PLAYER_1_6, EPONG_SPRITES::SCORE_PLAYER_1_7, EPONG_SPRITES::SCORE_PLAYER_1_8, EPONG_SPRITES::SCORE_PLAYER_1_9 };
	EPONG_SPRITES m_Player2Num[10]{ EPONG_SPRITES::SCORE_PLAYER_2_0, EPONG_SPRITES::SCORE_PLAYER_2_1, EPONG_SPRITES::SCORE_PLAYER_2_2, EPONG_SPRITES::SCORE_PLAYER_2_3, EPONG_SPRITES::SCORE_PLAYER_2_4, EPONG_SPRITES::SCORE_PLAYER_2_5, EPONG_SPRITES::SCORE_PLAYER_2_6, EPONG_SPRITES::SCORE_PLAYER_2_7, EPONG_SPRITES::SCORE_PLAYER_2_8, EPONG_SPRITES::SCORE_PLAYER_2_9 };
};