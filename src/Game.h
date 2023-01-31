#pragma once
#include <vector>
#include <memory>

#include "Impact.h"
#include "Bat.h"
#include "Ball.h"

class Game 
{
public:
	~Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	static std::shared_ptr<Game> getInstance();

	void update();
	void draw();

	void reset(int players);
	void playSound(std::string& sound, int count = 1, bool isMenu = false);
	void printScores();

	Ball& getBall();
	std::vector<std::unique_ptr<Bat>>& getBats();
	std::vector<std::unique_ptr<Impact>>& getImpacts();

	float getAIOffset() { return m_AI_Offset; }
	void setAIOffset(float value) { m_AI_Offset = value; }

private:
	Game(int players);
	static std::shared_ptr<Game> m_Instance;

	void createPlayers(int players);
	std::vector<std::unique_ptr<Impact>> m_Impacts;
	std::vector<std::unique_ptr<Bat>> m_Bats;

	Ball m_Ball{ *this, -1.f };
	float m_AI_Offset{ 0.f };
};