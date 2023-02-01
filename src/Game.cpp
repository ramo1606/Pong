#include "Game.h"
#include "Common.h"
#include "ResourceManager.h"

#include <string>

using namespace Common;

std::shared_ptr<Game> Game::m_Instance = nullptr;

Game::Game(int players)
{
	createPlayers(players);
}

Game::~Game()
{
}

std::shared_ptr<Game> Game::getInstance()
{
	if (!m_Instance)
		m_Instance.reset(new Game(0));
	return m_Instance;
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

	auto impactIt = m_Impacts.begin();
	while (impactIt != m_Impacts.end())
	{
		Impact* impact = *impactIt;
		if (impact->getTime() >= 10)
		{
			impact->~Impact();
			ObjPoolFree(&m_ImpactsPool, impact);
			impact = nullptr;
			impactIt = m_Impacts.erase(impactIt);
		}
		else {
			++impactIt;
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

	for (int i = 0; i < m_Bats.size(); ++i) 
	{
		m_Bats[i]->~Bat();
		ObjPoolFree(&m_BatsPool, m_Bats[i]);
		m_Bats[i] = nullptr;
	}

	for (int i = 0; i < m_Impacts.size(); ++i)
	{
		m_Impacts[i]->~Impact();
		ObjPoolFree(&m_ImpactsPool, m_Impacts[i]);
		m_Impacts[i] = nullptr;
	}

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

Bat& Game::getBat(Player player) const
{
	return *m_Bats[static_cast<int>(player)];
}

void Game::addImpact(Vector2 pos)
{
	Impact* impact = static_cast<Impact*>(ObjPoolAlloc(&m_ImpactsPool));
	new(impact) Impact(pos);
	m_Impacts.push_back(impact);
}

void Game::createPlayers(int players)
{
	bool player1_ai = players == 1 || players == 2 ? false : true;
	bool player2_ai = players == 2 ? false : true;

	Bat* player1 = static_cast<Bat*>(ObjPoolAlloc(&m_BatsPool));
	new(player1) Bat(Player::Player1, player1_ai);

	Bat* player2 = static_cast<Bat*>(ObjPoolAlloc(&m_BatsPool));
	new(player2) Bat(Player::Player2, player2_ai);

	m_Bats.push_back(player1);
	m_Bats.push_back(player2);
}
