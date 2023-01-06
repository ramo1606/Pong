#pragma once
#include <string>
#include <cmath>

namespace Common 
{
    enum class EPONG_SPRITES : std::uint8_t
    {
        MENU_0,
        MENU_1,
        GAME_OVER,
        TABLE,
        BALL,
        BAT_1,
        BAT_1_LIGHT,
        BAT_1_SHADOW,
        BAT_2,
        BAT_2_LIGHT,
        BAT_2_SHADOW,
        EFFECT_0,
        EFFECT_1,
        IMPACT_0,
        IMPACT_1,
        IMPACT_2,
        IMPACT_3,
        IMPACT_4,
        SCORE_0,
        SCORE_1,
        SCORE_2,
        SCORE_3,
        SCORE_4,
        SCORE_5,
        SCORE_6,
        SCORE_7,
        SCORE_8,
        SCORE_9,
        SCORE_PLAYER_1_0,
        SCORE_PLAYER_1_1,
        SCORE_PLAYER_1_2,
        SCORE_PLAYER_1_3,
        SCORE_PLAYER_1_4,
        SCORE_PLAYER_1_5,
        SCORE_PLAYER_1_6,
        SCORE_PLAYER_1_7,
        SCORE_PLAYER_1_8,
        SCORE_PLAYER_1_9,
        SCORE_PLAYER_2_0,
        SCORE_PLAYER_2_1,
        SCORE_PLAYER_2_2,
        SCORE_PLAYER_2_3,
        SCORE_PLAYER_2_4,
        SCORE_PLAYER_2_5,
        SCORE_PLAYER_2_6,
        SCORE_PLAYER_2_7,
        SCORE_PLAYER_2_8,
        SCORE_PLAYER_2_9
    };

    enum class EPONG_SOUNDS : std::uint8_t
    {
        BOUNCE_SYNTH,
        BOUNCE_0,
        BOUNCE_1,
        BOUNCE_2,
        BOUNCE_3,
        BOUNCE_4,
        DOWN,
        UP,
        HIT_SYNTH,
        HIT_SLOW,
        HIT_MEDIUM,
        HIT_FAST,
        HIT_VERY_FAST,
        HIT_0,
        HIT_1,
        HIT_2,
        HIT_3,
        HIT_4,
        SCORE_GOAL
    };

    enum class EPONG_MUSIC : std::uint8_t
    {
        THEME
    };

    const std::string TITLE = "Boing!";

    constexpr int WIDTH = 800;
    constexpr int HEIGHT = 480;
    constexpr float HALF_WIDTH = WIDTH * 0.5;
    constexpr float HALF_HEIGHT = HEIGHT * 0.5;

    constexpr float PLAYER_SPEED = 6;
    constexpr float MAX_AI_SPEED = 6;

    constexpr int PLAYER1_INITIAL_X_POS = 40;
    constexpr int PLAYER2_INITIAL_X_POS = 760;
    constexpr int PLAYER_INITIAL_Y_POS = HALF_HEIGHT;
}
