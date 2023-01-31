#include "Game.h"
#include "Common.h"
#include "ResourceManager.h"

#include <string>

using namespace Common;

Game::Game(int players)
{
	createPlayers(players);
}

void Game::update()
{
	for (auto& bat : m_Bats) 
	{
		bat->update();
	}

	for (auto& impact : m_Impacts)
	{
		impact->update();
	}

	m_Ball.update();

	for (int i = m_Impacts.size()-1; i >= 0; --i) 
	{
		if (m_Impacts[i]->getTime() >= 10) 
		{
			m_Impacts.erase(m_Impacts.end() - (i+1));
		}
	}

	int scoring_player = 0;
	int losing_player = 0;
	if (m_Ball.out()) 
	{
		scoring_player = m_Ball.getPosition().x < WIDTH * 0.5f ? 1 : 0;
		losing_player = 1 - scoring_player;

		if (m_Bats[losing_player]->getTimer() < 0) 
		{
			m_Bats[scoring_player]->addScore();

			//Play Sound
			playSound(std::string("score_goal"), 1);

			m_Bats[losing_player]->setTimer(20);
		}
		else if (m_Bats[losing_player]->getTimer() == 0)
		{
			int direction = losing_player == 0 ? -1 : 1;
			m_Ball.reset(direction);
		}
	}
}

void Game::draw()
{
	DrawTexture(*ResourceManager::getSprite(std::string("table")), 0, 0, WHITE);

	for (auto& bat : m_Bats) 
	{
		if (bat->getTimer() > 0 && m_Ball.out()) 
		{
			std::string effect = bat->getPlayer() == Player::Player1 ? "0" : "1";
			DrawTexture(*ResourceManager::getSprite(std::string("effect") + effect), 0, 0, WHITE);
		}
	}

	for (auto& bat : m_Bats)
	{
		bat->draw();
	}

	for (auto& impact : m_Impacts)
	{
		impact->draw();
	}

	m_Ball.draw();

	printScores();
}

void Game::reset(int players)
{
	m_Ball.reset(-1);
	m_AI_Offset = 0.f;

	m_Bats.clear();
	m_Impacts.clear();

	createPlayers(players);
}

void Game::playSound(std::string& sound, int count, bool isMenu)
{
	if (!m_Bats[0]->isAI() || isMenu) 
	{
		PlaySound(*ResourceManager::getSound(sound + std::to_string(GetRandomValue(0, count - 1))));
	}
}

void Game::printScores()
{
	for (int player = 0; player <= 1; ++player)
	{
		std::string score = std::to_string(m_Bats[player]->getScore() / 10) + std::to_string(m_Bats[player]->getScore() % 10);

		for (int i = 0; i <= 1; ++i)
		{
			std::string color = "0";
			int otherPlayer = 1 - player;
			if (m_Bats[otherPlayer]->getTimer() > 0 && m_Ball.out()) 
			{
				color = player == 0 ? "2" : "1";
			}
			std::string image = "digit";
			image += color + score[i];
			DrawTexture(*ResourceManager::getSprite(image), 255 + (160 * player) + (i * 55), 46, WHITE);
		}
	}
}

Ball& Game::getBall()
{
	return m_Ball;
}

std::vector<std::unique_ptr<Bat>>& Game::getBats()
{
	return m_Bats;
}

std::vector<std::unique_ptr<Impact>>& Game::getImpacts()
{
	return m_Impacts;
}

void Game::createPlayers(int players)
{
	bool player1_ai = players == 1 || players == 2 ? false : true;
	bool player2_ai = players == 2 ? false : true;
	m_Bats.push_back(std::make_unique<Bat>(*this, Player::Player1, player1_ai));
	m_Bats.push_back(std::make_unique<Bat>(*this, Player::Player2, player2_ai));
}
