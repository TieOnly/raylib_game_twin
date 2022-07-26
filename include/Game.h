#pragma once
#include <assert.h>
#include <string>
#include <random>
#include "raylibCpp.h"
#include "FrameTime.h"
#include "Character.h"
#include "FontC.h"
#include "Poo.h"
#include "Bullet.h"

class Game
{
public:
    Game(int fps);
    ~Game() noexcept;
    Game (const Game& another) = delete;
    Game& operator = (const Game& another) = delete;
    bool GameShouldClose() const;
    void Tick();
private:
    void Update();
    void Draw();

    FrameTime ft;
    const RectI screenRect = rayCpp::GetScreenRect();
    std::mt19937 rng;

    Texture2D pooS;
    Texture2D bulletS;

    Character elf = Character( {100, 100} );
    FontC font;
    std::vector<Poo> poos;

    std::vector<Bullet> bullets;
};
