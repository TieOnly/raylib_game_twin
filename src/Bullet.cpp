#include "Bullet.h"
#include "SpriteEffects.h"

Bullet::Bullet( const Vec2& pos, const Vec2& dir)
    :
    bullet_surf( LoadTexture("../assets/img/bullet.png") ),
    bullet_animation( 0, 0, 24, 24, 4, bullet_surf, 0.08f ),
    pos( pos ),
    vel( dir * speed )
{}
Bullet::Bullet( const Bullet& src )
    :
    bullet_surf( src.bullet_surf ),
    bullet_animation( 0, 0, 24, 24, 4, bullet_surf, 0.08f ),
    pos( src.pos ),
    vel( src.vel )
{}
Bullet& Bullet::operator = ( const Bullet& src )
{
    pos = src.pos;
    vel = src.vel;
    return *this;
}
void Bullet::Update( float dTime )
{
    pos += vel * dTime;
    bullet_animation.Update( dTime );
}
void Bullet::Draw() const
{
    const Vec2 draw_pos = pos + draw_offset;

    SpriteEffects::Chroma e{ WHITE };
    bullet_animation.Draw( draw_pos, e );
}
const Vec2& Bullet::GetPos() const
{
    return pos;
}
RectI Bullet::GetHitBox() const
{
    return RectI::FromCenter( (Vei2)pos, hwHitBox, hhHitBox );
}