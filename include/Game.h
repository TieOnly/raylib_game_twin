#pragma once
#include <assert.h>
#include <string>
#include "raylib.h"
#include "FrameTime.h"
#include "Character.h"
#include "FontC.h"
#include "Poo.h"

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

    Character elf = Character( {100, 100} );
    FontC font;
    std::vector<Poo> poos;
};
