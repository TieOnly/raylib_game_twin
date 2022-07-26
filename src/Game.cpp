#include "Game.h"
#include <iostream>
#include <cmath>

Game::Game(int fps)
    :
    rng( std::random_device()() ),
    pooS( LoadTexture("../assets/img/poo.png") ),
    bulletS( LoadTexture("../assets/img/bullet.png") ),
    font( "../assets/font/fontWhite.png" )
{
    SetTargetFPS(fps);
    std::uniform_real_distribution<float> xD( 0, (float)settings::screenW );
    std::uniform_real_distribution<float> yD( 0, (float)settings::screenH );

    for(int i = 0; i < 20; i++)
    {
        poos.emplace_back( Poo{ pooS, Vec2{xD( rng ), yD( rng )}} );
    }

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
        //const location spawn
        const Vec2 loca_offset = {0.0f, -20.0f};

        bullets.emplace_back( Bullet{ bulletS, elf.GetPos() + loca_offset, dir } );
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

    //
    for( Bullet& b : bullets )
    {
        b.Update( dTime );
    }

    //collision with bullets and elf
    for(Poo& poo : poos)
    {
        //move logic
        {
            bool avoiding = false;
            for( Poo& other : poos )
            {
                if( &poo == &other )
                {
                    continue;
                }
                const Vec2 delta = poo.GetPos() - other.GetPos();
                const float lensq = delta.GetLengthSq();
                if( lensq < 100.0f )
                {
                    avoiding = true;
                    if( lensq == 0.0f )
                    {
                        poo.SetDirection( {-1.0f, 0.0f} );
                    }
                    else
                    {
                        poo.SetDirection( delta / std::sqrt(lensq));
                    }
                    break;
                }
            }
            if(!avoiding)
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
            }
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
                poo.ApplyDamege( bullets[i].GetDamege() );
                rayCpp::remove_element( bullets, i );
            }
            else if( !bullets[i].GetHitBox().IsOverLapping( screenRect ) )
            {
                rayCpp::remove_element( bullets, i );
            }
            else
            {
                ++i;
            }
        }
    }
    //remove poo if dead
    for( size_t i = 0u; i < poos.size(); )
    {
        if(poos[i].IsDead())
        {
            rayCpp::remove_element( poos, i );
            continue;
        }
        ++i;
    }
}
void Game::Draw()
{
    ClearBackground(RAYWHITE);
    for( Poo& poo : poos )
    {
        poo.Draw();
        // rayCpp::DrawRectThin( poo.GetHitBox(), RED );
    }
    // rayCpp::DrawRectThin( elf.GetHitBox(), GREEN );
    elf.Draw();
    for( Bullet& b : bullets )
    {
        b.Draw();
        // rayCpp::DrawRectThin( b.GetHitBox(), SKYBLUE );
    }
    font.DrawText("From Chili with love~", {10, 10}, BLACK);
}
