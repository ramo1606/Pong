#pragma once
#include "Actor.h"

class Ball : public Actor 
{
public:
	Ball(float dx);
	Ball(const Ball&) = default;
	Ball& operator=(const Ball&) = default;
	~Ball() = default;

	void update() override;
	void reset(float dx);

	bool out() const;

private:
	float m_Dx{ 0.f };
	float m_Dy{ 0.f };

	int m_Speed{ 0 };
};