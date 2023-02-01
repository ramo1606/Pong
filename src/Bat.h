#pragma once
#include "Actor.h"

enum class Player : uint8_t 
{
	Player1,
	Player2
};

class Bat : public Actor
{
public:
	Bat(Player player, bool isAI = false);
	Bat(const Bat&) = default;
	Bat& operator=(const Bat&) = default;
	~Bat() = default;

	void processInput() override;
	void update() override;

	Player getPlayer() const { return m_Player; }
	int getTimer() const { return m_Timer; }
	uint8_t getScore() const { return m_Score; }
	
	void setTimer(int value) { m_Timer = value; }
	void addScore() { m_Score++; }
	
	float ai() const;
	bool isAI() const { return m_IsAI; }

private:
	void selectBatImage();

	float m_Dy{ 0 };
	
	Player m_Player = Player::Player1;
	uint8_t m_Score{ 0 };
	int m_Timer{ 0 };
	bool m_IsAI{ false };
};