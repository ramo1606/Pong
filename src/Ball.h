#pragma once
#include "Actor.h"

/*
* Ball Actor is the ball that will move around the screen and players have to hit
* It contains speed and direction of the ball
*/
class Ball : public Actor 
{
public:
	Ball(float dx);
	Ball(const Ball&) = default;
	Ball& operator=(const Ball&) = default;
	~Ball() = default;

	void update() override;
	void reset(float dx);

	//Check if the ball is out of the field boundary
	bool out() const;

private:
	int m_Speed{ 0 };
	Vector2 m_Direction{ 0.f, 0.f };
};