#pragma once
#include <string>
#include <cmath>

namespace Common 
{
    const std::string TITLE = "Boing!";

    constexpr int WIDTH = 800;
    constexpr int HEIGHT = 480;
    constexpr float HALF_WIDTH = WIDTH * 0.5;
    constexpr float HALF_HEIGHT = HEIGHT * 0.5;

    constexpr float PLAYER_SPEED = 6;
    constexpr float MAX_AI_SPEED = 6;

    constexpr float BALL_SPEED = 5;

    constexpr int PLAYER1_INITIAL_X_POS = 40;
    constexpr int PLAYER2_INITIAL_X_POS = 760;
    constexpr int PLAYER_INITIAL_Y_POS = HALF_HEIGHT;
}
