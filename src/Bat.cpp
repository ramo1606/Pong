#include "Bat.h"
#include "Common.h"
#include "ResourceManager.h"
#include "Game.h"

#include <algorithm>

using namespace Common;

Bat::Bat(Game& game, Player player, bool isAI)
	: Actor("Bat", { 0, 0 }, nullptr),
	  m_Game(&game),
	  m_Player(player),
	  m_IsAI(isAI)
{
	m_Pos.x = player == Player::Player1 ? PLAYER1_INITIAL_X_POS : PLAYER2_INITIAL_X_POS;
	m_Pos.y = PLAYER_INITIAL_Y_POS;
	selectBatImage();
}

void Bat::processInput()
{
	if (m_IsAI)
	{
		m_Dy = ai();
		return;
	}

	switch (m_Player)
	{
	case Player::Player1:
		if (IsKeyDown(KEY_Z) || IsKeyDown(KEY_DOWN))
			m_Dy = PLAYER_SPEED;
		else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_UP))
			m_Dy = -PLAYER_SPEED;
		break;
	case Player::Player2:
		if (IsKeyDown(KEY_M))
			m_Dy = PLAYER_SPEED;
		else if (IsKeyDown(KEY_K))
			m_Dy = -PLAYER_SPEED;
		break;
	default:
		break;
	}
}

void Bat::update()
{
	m_Timer--;

	processInput();
	m_Pos.y = std::min(400.f, std::max(80.f, m_Pos.y + m_Dy));
	m_Dy = 0;

	selectBatImage();
}

float Bat::ai()
{
	float x_distance = std::abs(m_Game->getBall().getPosition().x - m_Pos.x);
	float target_y_1 = HALF_HEIGHT;
	float target_y_2 = m_Game->getBall().getPosition().y + m_Game->getAIOffset();

	float weight1 = std::min(1.f, x_distance / HALF_WIDTH);
	float weight2 = 1.f - weight1;

	float target_y = (weight1 * target_y_1) + (weight2 * target_y_2);

	return std::min(MAX_AI_SPEED, std::max(-MAX_AI_SPEED, target_y - m_Pos.y));
}

void Bat::selectBatImage()
{
	EPONG_SPRITES bat_sprite = EPONG_SPRITES::BAT_1;
	switch (m_Player)
	{
	case Player::Player1:
		bat_sprite = EPONG_SPRITES::BAT_1;
		if (m_Timer > 0) 
		{
			bat_sprite = m_Game->getBall().out() ? EPONG_SPRITES::BAT_1_SHADOW : EPONG_SPRITES::BAT_1_LIGHT;
		}
		break;
	case Player::Player2:
		bat_sprite = EPONG_SPRITES::BAT_2;
		if (m_Timer > 0) 
		{
			bat_sprite = m_Game->getBall().out() ? EPONG_SPRITES::BAT_2_SHADOW : EPONG_SPRITES::BAT_2_LIGHT;
		}
		break;
	default:
		break;
	}

	m_Image = ResourceManager::getSprite(bat_sprite);
}
