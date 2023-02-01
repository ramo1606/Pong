#define RMEM_IMPLEMENTATION
#include "Ball.h"
#include "Bat.h"
#include "Game.h"
#include "ResourceManager.h"
#include "raymath.h"
#include "Common.h"

#include <algorithm>

using namespace Common;

Ball::Ball(float dx) : Actor("Ball", {0, 0}, ResourceManager::getSprite(std::string("ball")))
{
	//Initialize class with position at middle of the screen and given direction in the x axis.
	m_Pos.x = HALF_WIDTH;
	m_Pos.y = HALF_HEIGHT;

	m_Direction = { dx, 0.f };
	m_Speed = BALL_SPEED;
}

void Ball::update()
{
	std::shared_ptr<Game> gameInstance = Game::getInstance();

	for (int i = 0; i < m_Speed; ++i) 
	{
		//Store the original x position
		float original_x = m_Pos.x;

		//Move the ball
		m_Pos.x += m_Direction.x;
		m_Pos.y += m_Direction.y;

		// Check to see if ball needs to bounce off a bat
		/* 
		* To determine whether the ball might collide with a bat, we first measure the horizontal distance from the
		* ball to the centre of the screen, and check to see if its edge has gone beyond the edge of the bat.
		* The centre of each bat is 40 pixels from the edge of the screen, or to put it another way, 360 pixels
		* from the centre of the screen.The bat is 18 pixels wide and the ball is 14 pixels wide.Given that these
		* sprites are anchored from their centres, when determining if they overlap or touch, we need to look at
		* their half - widths - 9 and 7. Therefore, if the centre of the ball is 344 pixels from the centre of the
		* screen, it can bounce off a bat(assuming the bat is in the right position on the Y axis - checked
		* shortly afterwards).
		* We also check the previous X position to ensure that this is the first frame in which the ball crossed the threshold.
		*/
		if (std::abs(m_Pos.x - HALF_WIDTH) >= 344 && std::abs(original_x - HALF_WIDTH) < 344) 
		{

			float new_dir_x = 0.f;
			Bat* bat = nullptr;

			//If the ball is in the left of the middle of the screen then player one will collide with the ball
			if (m_Pos.x < HALF_WIDTH) 
			{
				new_dir_x = 1;
				bat = gameInstance->getBat(Player::Player1);
			}
			else 
			{
				new_dir_x = -1;
				bat = gameInstance->getBat(Player::Player2);
			}

			//Distance in y axis between ball and bat
			float difference_y = m_Pos.y - bat->getPosition().y;

			if (difference_y > -64 && difference_y < 64)
			{
				/*
				* Ball has collided with bat - calculate new direction vector

                *  To understand the maths used below, we first need to consider what would happen with this kind of
                *  collision in the real world. The ball is bouncing off a perfectly vertical surface. This makes for a
                *  pretty simple calculation. Let's take a ball which is travelling at 1 metre per second to the right,
                *  and 2 metres per second down. Imagine this is taking place in space, so gravity isn't a factor.
                *  After the ball hits the bat, it's still going to be moving at 2 m/s down, but it's now going to be
                *  moving 1 m/s to the left instead of right. So its speed on the y-axis hasn't changed, but its
                *  direction on the x-axis has been reversed. This is extremely easy to code - "self.dx = -self.dx".
                *  However, games don't have to perfectly reflect reality.
                *  In Pong, hitting the ball with the upper or lower parts of the bat would make it bounce diagonally
                *  upwards or downwards respectively. This gives the player a degree of control over where the ball
                *  goes. To make for a more interesting game, we want to use realistic physics as the starting point,
                *  but combine with this the ability to influence the direction of the ball. When the ball hits the
                *  bat, we're going to deflect the ball slightly upwards or downwards depending on where it hit the
                *  bat. This gives the player a bit of control over where the ball goes.
				*/

				//Invert x direction
				m_Direction.x = -m_Direction.x;

				//Deflect slightly up or down depending on where ball hit bat
				m_Direction.y += difference_y / 128.f;

				// Limit the Y component of the vector so we don't get into a situation where the ball is bouncing
				// upand down too rapidly
				m_Direction.y = std::min(std::max(m_Direction.y, -1.f), 1.f);

				// Ensure our direction vector is a unit vector, i.e. represents a distance of the equivalent of
				// 1 pixel regardless of its angle
				Vector2 normalized_velocity = Vector2Normalize({ m_Direction.x, m_Direction.y });
				m_Direction.x = normalized_velocity.x;
				m_Direction.y = normalized_velocity.y;

				// Add impact effect
				Vector2 pos = { m_Pos.x - new_dir_x * 10.f, m_Pos.y };
				gameInstance->addImpact(pos);

				//Increase speed every hit
				m_Speed += 1;

				// Add an offset to the AI player's target Y position, so it won't aim to hit the ball exactly
				// in the centre of the bat
				gameInstance->setAIOffset(GetRandomValue(-10, 10));

				// Bat glows for 10 frames
				bat->setTimer(10);

				//Play Sounds
				//Play hit every time plus another sound depending on speed
				gameInstance->playSound(std::string("hit"), 5);
				if (m_Speed <= 10)
				{
					gameInstance->playSound(std::string("hit_slow"));
				}
				else if (m_Speed <= 12) 
				{
					gameInstance->playSound(std::string("hit_medium"));
				}
				else if (m_Speed <= 16) 
				{
					gameInstance->playSound(std::string("hit_fast"));
				}
				else 
				{
					Game::getInstance()->playSound(std::string("hit_veryfast"));
				}
			}
		}

		//Checks if the ball have reached top or bottom
		if(std::abs(m_Pos.y - HALF_HEIGHT) > 220)
		{
			//Change y direction and add to y position so now the ball is not overlapping the edge
			m_Direction.y = -m_Direction.y;
			m_Pos.y += m_Direction.y;

			//Create impact effect in the impact position
			gameInstance->addImpact(m_Pos);

			//Play Sounds effect
			gameInstance->playSound(std::string("bounce"), 5);
			gameInstance->playSound(std::string("bounce_synth"));
		}
	}
}

void Ball::reset(float dx)
{
	//Reset values to default
	m_Image = ResourceManager::getSprite(std::string("ball"));

	m_Direction.x = dx;
	m_Direction.y = 0.f;

	m_Pos.x = HALF_WIDTH;
	m_Pos.y = HALF_HEIGHT;

	m_Speed = BALL_SPEED;
}

bool Ball::out() const
{
	//The ball is outside of the screen
	return m_Pos.x < 0.f || m_Pos.x > WIDTH;
}
