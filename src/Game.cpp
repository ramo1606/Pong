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
	// Update all active objects
	for (auto& bat : m_Bats) 
	{
		bat->update();
	}

	for (auto& impact : m_Impacts)
	{
		impact->update();
	}

	m_Ball.update();

	/*
	* Remove any expired impact effects from the list.
	*/
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
		/*
		* Work out which player gained a point, based on whether the ball
		* was on the left or right - hand side of the screen
		*/ 
		scoring_player = m_Ball.getPosition().x < WIDTH * 0.5f ? 1 : 0;
		losing_player = 1 - scoring_player;

		/*
		* We use the timer of the player who has just conceded a point to decide when to create a new ball in the
        * centre of the level. This timer starts at zero at the beginning of the game and counts down by one every
        * frame. Therefore, on the frame where the ball first goes off the screen, the timer will be less than zero.
        * We set it to 20, which means that this player's bat will display a different animation frame for 20
        * frames, and a new ball will be created after 20 frames
		*/
		if (m_Bats[losing_player]->getTimer() < 0) 
		{
			m_Bats[scoring_player]->addScore();

			//Play Sound
			playSound(std::string("score_goal"), 1);

			m_Bats[losing_player]->setTimer(20);
		}
		else if (m_Bats[losing_player]->getTimer() == 0)
		{
			// After 20 frames, create a new ball, heading in the direction of the player who just missed the ball
			int direction = losing_player == 0 ? -1 : 1;
			m_Ball.reset(direction);
		}
	}
}

void Game::draw()
{
	// Draw background
	DrawTexture(*ResourceManager::getSprite(std::string("table")), 0, 0, WHITE);

	// Draw Effect	
	for (auto& bat : m_Bats) 
	{
		if (bat->getTimer() > 0 && m_Ball.out())
		{
			std::string effect = bat->getPlayer() == Player::Player1 ? "0" : "1";
			DrawTexture(*ResourceManager::getSprite(std::string("effect") + effect), 0, 0, WHITE);
		}
	}

	// Draw Bats
	for (auto& bat : m_Bats)
	{
		bat->draw();
	}

	// Draw Impacts
	for (auto& impact : m_Impacts)
	{
		impact->draw();
	}

	// Draw Ball
	m_Ball.draw();

	// Print Score
	printScores();
}

void Game::reset(int players)
{
	// Reset game, set all values at default values
	m_Ball.reset(-1);
	m_AI_Offset = 0.f;

	// Clean ObjPool memory
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

	// Clear bats and impacts vector
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

Ball* Game::getBall()
{
	// Return ball
	return &m_Ball;
}

Bat* Game::getBat(Player player) const
{
	// Return bat correspondig to given player
	return m_Bats[static_cast<int>(player)];
}

void Game::addImpact(Vector2 pos)
{
	// Create new impact in the ImpactsPool and add it to impacts list 
	Impact* impact = static_cast<Impact*>(ObjPoolAlloc(&m_ImpactsPool));
	new(impact) Impact(pos);
	m_Impacts.push_back(impact);
}

void Game::createPlayers(int players)
{
	/* 
	* Create a list of two bats, giving each a player number
	*/ 
	bool player1_ai = players == 1 || players == 2 ? false : true;
	bool player2_ai = players == 2 ? false : true;

	// Alloc memory in the bats ObjectPool and create the bats
	Bat* player1 = static_cast<Bat*>(ObjPoolAlloc(&m_BatsPool));
	new(player1) Bat(Player::Player1, player1_ai);

	Bat* player2 = static_cast<Bat*>(ObjPoolAlloc(&m_BatsPool));
	new(player2) Bat(Player::Player2, player2_ai);

	// Add the bat reference to the bat list
	m_Bats.push_back(player1);
	m_Bats.push_back(player2);
}
