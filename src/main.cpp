#include "raylib.h"
#include "Common.h"
#include "ResourceManager.h"
#include "Game.h"

using namespace Common;

//TODO: make resourcesmanager and game a real singleton
//TODO: get rid of magic numbers
//TODO: comment code

enum class State : uint8_t 
{
    MENU,
    PLAY,
    GAME_OVER
};

class Pong 
{
public:
    Pong() 
    {
    }

    void update()
    {
        bool space_pressed = false;
        if ((IsKeyDown(KEY_SPACE) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_MIDDLE_RIGHT)) && !m_SpaceDown)
        {
            space_pressed = true;
        }

        m_SpaceDown = IsKeyDown(KEY_SPACE) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_MIDDLE_RIGHT);

        switch (m_State)
        {
        case State::MENU:
            if (space_pressed)
            {
                m_State = State::PLAY;
                Game::getInstance()->reset(m_NumPlayers);
            }
            else
            {
                if (m_NumPlayers == 1 && (IsKeyDown(KEY_DOWN) || GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) == 1))
                {
                    //Play sound
                    Game::getInstance()->playSound(std::string("down"), 1, true);
                    m_NumPlayers = 2;
                }
                else if (m_NumPlayers == 2 && (IsKeyDown(KEY_UP) || GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) == -1))
                {
                    //Play sound
                    Game::getInstance()->playSound(std::string("up"), 1, true);
                    m_NumPlayers = 1;
                }
                Game::getInstance()->update();
            }
            break;
        case State::PLAY:
            //Has anyone won?
            if (std::max(Game::getInstance()->getBat(Player::Player1).getScore(), Game::getInstance()->getBat(Player::Player2).getScore()) > 9)
            {
                m_State = State::GAME_OVER;
            }
            else
            {
                Game::getInstance()->update();
            }
            break;
        case State::GAME_OVER:
            if (space_pressed)
            {
                //Reset to menu state
                m_State = State::MENU;
                m_NumPlayers = 0;

                Game::getInstance()->reset(m_NumPlayers);
                m_NumPlayers = 1;
            }
            break;
        default:
            break;
        }
    }

    void draw()
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        Game::getInstance()->draw();

        switch (m_State)
        {
        case State::MENU:
            if (m_NumPlayers == 1 || m_NumPlayers == 0)
                DrawTexture(*ResourceManager::getSprite(std::string("menu0")), 0, 0, WHITE);
            if (m_NumPlayers == 2)
                DrawTexture(*ResourceManager::getSprite(std::string("menu1")), 0, 0, WHITE);
            break;
        //case State::PLAY:
        //    m_Game.draw();
        //    break;
        case State::GAME_OVER:
            DrawTexture(*ResourceManager::getSprite(std::string("over")), 0, 0, WHITE);
            break;
        default:
            break;
        }

        EndDrawing();
    }
private:
    bool m_SpaceDown{ false };
    State m_State{ State::MENU };
    uint8_t m_NumPlayers{ 1 };
};


int main(void)
{
    InitWindow(WIDTH, HEIGHT, TITLE.c_str());
    InitAudioDevice();
    SetTargetFPS(60);

    ResourceManager resourceManager;
    resourceManager.loadResources();

    Pong pong;

    PlayMusicStream(*ResourceManager::getMusic(std::string("theme")));
    SetMusicVolume(*ResourceManager::getMusic(std::string("theme")), 0.5f);

    while (!WindowShouldClose())
    {
        UpdateMusicStream(*ResourceManager::getMusic(std::string("theme")));
        pong.update();
        pong.draw();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
