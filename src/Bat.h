#pragma once
#include "Actor.h"

class Game;

enum class Player : uint8_t 
{
	Player1,
	Player2
};

class Bat : public Actor
{
public:
	Bat(Game& game, Player player, bool isAI = false);
	Bat(const Bat&) = default;
	Bat& operator=(const Bat&) = default;

	void processInput() override;
	void update() override;
	
	float ai();
	int getTimer() { return m_Timer; }
	void setTimer(int value) { m_Timer = value; }
	Player getPlayer() { return m_Player; }
	uint8_t getScore() { return m_Score; }
	void addScore() { m_Score++; }
	bool isAI() { return m_IsAI; }

private:
	void selectBatImage();

	Game* m_Game = nullptr;
	Player m_Player = Player::Player1;
	uint8_t m_Score{ 0 };
	int m_Timer{ 0 };
	float m_Dy{ 0 };
	bool m_IsAI{ false };
};