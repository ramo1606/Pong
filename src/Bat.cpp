#include "Bat.h"
#include "Common.h"
#include "ResourceManager.h"
#include "Ball.h"
#include "Game.h"

#include <algorithm>

using namespace Common;

Bat::Bat(Player player, bool isAI)
	: Actor("Bat", { 0, 0 }, nullptr),
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
		if (IsKeyDown(KEY_Z) || IsKeyDown(KEY_DOWN) || GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) == 1)
			m_Dy = PLAYER_SPEED;
		else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_UP) || GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) == -1)
			m_Dy = -PLAYER_SPEED;
		break;
	case Player::Player2:
		if (IsKeyDown(KEY_M) || GetGamepadAxisMovement(1, GAMEPAD_AXIS_LEFT_Y) == 1)
			m_Dy = PLAYER_SPEED;
		else if (IsKeyDown(KEY_K) || GetGamepadAxisMovement(1, GAMEPAD_AXIS_LEFT_Y) == -1)
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

float Bat::ai() const
{
	float x_distance = std::abs(Game::getInstance()->getBall().getPosition().x - m_Pos.x);
	float target_y_1 = HALF_HEIGHT;
	float target_y_2 = Game::getInstance()->getBall().getPosition().y + Game::getInstance()->getAIOffset();

	float weight1 = std::min(1.f, x_distance / HALF_WIDTH);
	float weight2 = 1.f - weight1;

	float target_y = (weight1 * target_y_1) + (weight2 * target_y_2);

	return std::min(MAX_AI_SPEED, std::max(-MAX_AI_SPEED, target_y - m_Pos.y));
}

void Bat::selectBatImage()
{
	int frame = 0;
	if (m_Timer > 0) 
	{
		frame = Game::getInstance()->getBall().out() ? 2 : 1;
	}

	m_Image = ResourceManager::getSprite(std::string("bat") + std::to_string(static_cast<int>(m_Player)) + std::to_string(frame));
}
