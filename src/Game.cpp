#include "Game.h"
#include "raylib.h"

Game::Game(int fps)
    :
    font( "../assets/font/fontWhite.png" )
{
    SetTargetFPS(fps);
    poos.emplace_back( Vec2{50, 50} );
    poos.emplace_back( Vec2{50, 550} );
    poos.emplace_back( Vec2{750, 50} );
    poos.emplace_back( Vec2{750, 550} );
}
Game::~Game() noexcept
{
    assert(GetWindowHandle());
    CloseWindow();
}
bool Game::GameShouldClose() const
{
    return WindowShouldClose();
}
void Game::Tick() 
{
    BeginDrawing();
    Update();
    Draw();
    EndDrawing();
}
void Game::Update()
{
    const float dTime = ft.Mark();

    Vec2 dir = { 0, 0 };
    if(IsKeyDown(KEY_UP))
    {
        dir.y -= 1;
    }
    if( IsKeyDown(KEY_DOWN) )
    {
        dir.y += 1;
    }
    if( IsKeyDown(KEY_LEFT) )
    {
        dir.x -= 1;
    }
    if( IsKeyDown(KEY_RIGHT) )
    {
        dir.x += 1;
    }
    elf.SetDirection( dir );
    elf.Update( dTime );

    for(Poo& poo : poos)
    {
        const Vec2 delta = elf.GetPos() - poo.GetPos();

        if(delta.GetLengthSq() > 3.0f)
        {
            poo.SetDirection( delta.GetNormalize() );
        }
        else
        {
            poo.SetDirection( {0.0f, 0.0f} );
        }
        poo.Update( dTime );
        if( !elf.IsInvisible() && elf.GetHitBox().IsOverLapping( poo.GetHitBox() ) )
        {
            elf.ApplyEffect();
        }
    }
}
void Game::Draw()
{
    ClearBackground(RAYWHITE);
    for( Poo& poo : poos )
    {
        poo.Draw();
        rayCpp::DrawRectThin( poo.GetHitBox(), RED );
    }
    rayCpp::DrawRectThin( elf.GetHitBox(), GREEN );
    elf.Draw();
    // font.DrawText("From Chili\nwith love~", {GetMouseX(), GetMouseY()}, WHITE);
}
