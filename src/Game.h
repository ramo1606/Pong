#pragma once
#include <vector>
#include <memory>

#include "Impact.h"
#include "Bat.h"
#include "Ball.h"

#include "rmem.h"

/*
* Main class for the game logic, it creates and manages all the actors needed in the scene.
*/
class Game 
{
public:
	~Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	static std::shared_ptr<Game> getInstance();

	void update();
	void draw();

	void reset(int players);
	void playSound(std::string& sound, int count = 1, bool isMenu = false);
	void printScores();

	Ball* getBall();
	Bat* getBat(Player player) const ;
	void addImpact(Vector2 pos);

	float getAIOffset() const { return m_AI_Offset; }
	void setAIOffset(float value) { m_AI_Offset = value; }

private:
	Game(int players);
	static std::shared_ptr<Game> m_Instance;

	void createPlayers(int players);

	std::vector<Impact*> m_Impacts;
	std::vector<Bat*> m_Bats;

	// We use the rmem library to use ObjPool class to keep memory allocation at minimum
	ObjPool m_BatsPool = CreateObjPool(sizeof(Bat), 2);
	ObjPool m_ImpactsPool = CreateObjPool(sizeof(Impact), 10);

	Ball m_Ball { -1 };
	float m_AI_Offset{ 0.f };
};