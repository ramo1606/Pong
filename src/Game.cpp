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
			playSound(EPONG_SOUNDS::SCORE_GOAL);

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
	DrawTexture(*ResourceManager::getSprite(EPONG_SPRITES::TABLE), 0, 0, WHITE);

	for (auto& bat : m_Bats) 
	{
		if (bat->getTimer() > 0 && m_Ball.out()) 
		{
			EPONG_SPRITES effect = bat->getPlayer() == Player::Player1 ? EPONG_SPRITES::EFFECT_0 : EPONG_SPRITES::EFFECT_1;
			DrawTexture(*ResourceManager::getSprite(effect), 0, 0, WHITE);
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

void Game::playSound(EPONG_SOUNDS sound, bool isMenu)
{
	if (!m_Bats[0]->isAI() || isMenu) 
	{
		PlaySound(*ResourceManager::getSound(sound));
	}
}

void Game::printScores()
{
	EPONG_SPRITES player1ScoreDigit0 = m_Bats[1]->getTimer() > 0 && m_Ball.out() ? m_Player1Num[m_Bats[0]->getScore() / 10] : m_GreyNum[m_Bats[0]->getScore() / 10];
	EPONG_SPRITES player1ScoreDigit1 = m_Bats[1]->getTimer() > 0 && m_Ball.out() ? m_Player1Num[m_Bats[0]->getScore() % 10] : m_GreyNum[m_Bats[0]->getScore() % 10];
	
	EPONG_SPRITES player2ScoreDigit0 = m_Bats[0]->getTimer() > 0 && m_Ball.out() ? m_Player2Num[m_Bats[1]->getScore() / 10] : m_GreyNum[m_Bats[1]->getScore() / 10];
	EPONG_SPRITES player2ScoreDigit1 = m_Bats[0]->getTimer() > 0 && m_Ball.out() ? m_Player2Num[m_Bats[1]->getScore() % 10] : m_GreyNum[m_Bats[1]->getScore() % 10];
	
	DrawTexture(*ResourceManager::getSprite(player1ScoreDigit0), 255, 46, WHITE);
	DrawTexture(*ResourceManager::getSprite(player1ScoreDigit1), 310, 46, WHITE);
	DrawTexture(*ResourceManager::getSprite(player2ScoreDigit0), 415, 46, WHITE);
	DrawTexture(*ResourceManager::getSprite(player2ScoreDigit1), 470, 46, WHITE);
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
