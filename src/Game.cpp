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

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vec2 dir = Vec2{ (float)GetMouseX(), (float)GetMouseY() } - elf.GetPos();

        if( dir == (Vec2){ 0.0f, 0.0f } )
        {
            dir = { 0.0f, 1.0f };
        }
        else
        {
            dir.Nomarlize();
        }

        bullets.emplace_back( Bullet{ elf.GetPos(), dir } );
    }

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

    for( Bullet& b : bullets )
    {
        b.Update( dTime );
    }

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

        const auto poo_hitbox = poo.GetHitBox();
        if( !elf.IsInvisible() && elf.GetHitBox().IsOverLapping( poo.GetHitBox() ) )
        {
            elf.ApplyEffect();
        }
        for( size_t i = 0u; i < bullets.size(); )
        {
            if( bullets[i].GetHitBox().IsOverLapping( poo_hitbox ) )
            {
                rayCpp::remove_element( bullets, i );
                poo.ActivateEffect();
            }
            else
            {
                ++i;
            }
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
    for( Bullet& b : bullets )
    {
        b.Draw();
        rayCpp::DrawRectThin( b.GetHitBox(), SKYBLUE );
    }
    font.DrawText("From Chili with love~", {10, 10}, WHITE);
}
