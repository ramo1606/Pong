#include "Bat.h"
#include "Common.h"
#include "ResourceManager.h"
#include "Ball.h"
#include "Game.h"

#include <algorithm>

using namespace Common;

Bat::Bat(Player player, bool isAI) : Actor("Bat", { 0, 0 }, nullptr),
	  m_Player(player),
	  m_IsAI(isAI)
{
	//Set initial position of the bat depending on player
	m_Pos.x = player == Player::Player1 ? PLAYER1_INITIAL_X_POS : PLAYER2_INITIAL_X_POS;
	m_Pos.y = PLAYER_INITIAL_Y_POS;
	selectBatImage();
}

void Bat::processInput()
{
	//If the player is AI then call the ai() function to get the Y movement
	if (m_IsAI)
	{
		m_Dy = ai();
		return;
	}

	// Depending on the player we move the bats on Y axis by PLAYER_SPEED
	// The game supports keyborad keys and also gamepad inputs
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

	// Apply y_movement to y position, ensuring bat does not go through the side walls
	m_Pos.y = std::min(400.f, std::max(80.f, m_Pos.y + m_Dy));
	m_Dy = 0;

	selectBatImage();
}

float Bat::ai() const
{
	/*
	* Returns a number indicating how the computer player will move - e.g. 4 means it will move 4 pixels down
    * the screen.
    * To decide where we want to go, we first check to see how far we are from the ball.
	*/
	float x_distance = std::abs(Game::getInstance()->getBall()->getPosition().x - m_Pos.x);

	/* 
	* If the ball is far away, we move towards the centre of the screen(HALF_HEIGHT), on the basis that we don't
	* yet know whether the ball will be in the top or bottom half of the screen when it reaches our position on
	* the X axis.By waiting at a central position, we're as ready as it's possible to be for all eventualities.
	*/
	float target_y_1 = HALF_HEIGHT;

	/*
	* If the ball is close, we want to move towards its position on the Y axis. We also apply a small offset which
    * is randomly generated each time the ball bounces. This is to make the computer player slightly less robotic
    * - a human player wouldn't be able to hit the ball right in the centre of the bat each time.
	*/
	float target_y_2 = Game::getInstance()->getBall()->getPosition().y + Game::getInstance()->getAIOffset();

	/*
	* The final step is to work out the actual Y position we want to move towards. We use what's called a weighted
    * average - taking the average of the two target Y positions we've previously calculated, but shifting the
    * balance towards one or the other depending on how far away the ball is. If the ball is more than 400 pixels
    * (half the screen width) away on the X axis, our target will be half the screen height (target_y_1). If the
    * ball is at the same position as us on the X axis, our target will be target_y_2. If it's 200 pixels away,
    * we'll aim for halfway between target_y_1 and target_y_2. This reflects the idea that as the ball gets closer,
    * we have a better idea of where it's going to end up.
	*/
	float weight1 = std::min(1.f, x_distance / HALF_WIDTH);
	float weight2 = 1.f - weight1;

	float target_y = (weight1 * target_y_1) + (weight2 * target_y_2);

	/*
	* Subtract target_y from our current Y position, then make sure we can't move any further than MAX_AI_SPEED
    * each frame
	*/
	return std::min(MAX_AI_SPEED, std::max(-MAX_AI_SPEED, target_y - m_Pos.y));
}

void Bat::selectBatImage()
{
	/*
	* Choose the appropriate sprite.There are 3 sprites per player - e.g.bat00 is the left - hand player's
	* standard bat sprite, bat01 is the sprite to use when the ball has just bounced off the bat, and bat02
	* is the sprite to use when the bat has just missed the balland the ball has gone out of bounds.
	* bat10, 11 and 12 are the equivalents for the right - hand player
	*/
	int frame = 0;
	if (m_Timer > 0) 
	{
		frame = Game::getInstance()->getBall()->out() ? 2 : 1;
	}

	m_Image = ResourceManager::getSprite(std::string("bat") + std::to_string(static_cast<int>(m_Player)) + std::to_string(frame));
}
