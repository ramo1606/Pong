#include "Ball.h"
#include "Bat.h"
#include "Game.h"
#include "ResourceManager.h"
#include "raymath.h"

#include <algorithm>

Ball::Ball(Game& game, float dx) : Actor("Ball", {0, 0}, nullptr), m_Game(&game)
{
	m_Image = ResourceManager::getSprite(std::string("ball"));

	m_Dx = dx;
	m_Dy = 0.f;
	
	m_Pos.x = HALF_WIDTH;
	m_Pos.y = HALF_HEIGHT;

	m_Speed = 5;
}

void Ball::update()
{
	for (int i = 0; i < m_Speed; ++i) 
	{
		float original_x = m_Pos.x;

		m_Pos.x += m_Dx;
		m_Pos.y += m_Dy;

		if (std::abs(m_Pos.x - HALF_WIDTH) >= 344 && std::abs(original_x - HALF_WIDTH) < 344) 
		{
			float new_dir_x = 0.f;
			Bat* bat;
			if (m_Pos.x < HALF_WIDTH) 
			{
				new_dir_x = 1;
				bat = m_Game->getBats()[0].get();
			}
			else 
			{
				new_dir_x = -1;
				bat = m_Game->getBats()[1].get();
			}

			float difference_y = m_Pos.y - bat->getPosition().y;

			if (difference_y > -64 && difference_y < 64)
			{
				m_Dx = -m_Dx;
				m_Dy += difference_y / 128;

				m_Dy = std::min(std::max(m_Dy, -1.f), 1.f);

				Vector2 normalized_velocity = Vector2Normalize({ m_Dx, m_Dy });

				m_Dx = normalized_velocity.x;
				m_Dy = normalized_velocity.y;

				Vector2 pos = { m_Pos.x - new_dir_x * 10.f, m_Pos.y };
				m_Game->getImpacts().push_back(std::make_unique<Impact>(pos));

				m_Speed += 1;

				m_Game->setAIOffset(GetRandomValue(-10, 10));
				bat->setTimer(10);

				//Play Sounds
				m_Game->playSound(std::string("hit"), 5);
				if (m_Speed <= 10)
				{
					m_Game->playSound(std::string("hit_slow"));
				}
				else if (m_Speed <= 12) 
				{
					m_Game->playSound(std::string("hit_medium"));
				}
				else if (m_Speed <= 16) 
				{
					m_Game->playSound(std::string("hit_fast"));
				}
				else 
				{
					m_Game->playSound(std::string("hit_veryfast"));
				}
			}
		}

		if(std::abs(m_Pos.y - HALF_HEIGHT) > 220)
		{
			m_Dy = -m_Dy;
			m_Pos.y = m_Pos.y;

			m_Game->getImpacts().push_back(std::make_unique<Impact>(m_Pos));

			//Play Sounds
			m_Game->playSound(std::string("bounce"), 5);
			m_Game->playSound(std::string("bounce_synth"));
		}
	}
}

void Ball::reset(int direction)
{
	m_Dx = direction;
	m_Dy = 0.f;

	m_Pos.x = HALF_WIDTH;
	m_Pos.y = HALF_HEIGHT;

	m_Speed = 5;
}

bool Ball::out()
{
	return m_Pos.x < 0.f || m_Pos.x > WIDTH;
}
