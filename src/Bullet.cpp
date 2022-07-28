#include "Bullet.h"
#include "SpriteEffects.h"

Bullet::Bullet( const Vec2& pos, const Vec2& dir )
    :
    bullet_surf( Codex::Retrieve( "../assets/img/bullet2.png" ) ),
    bullet_animation( 0, 0, 60, 60, 5, bullet_surf, 0.16f ),
    pos( pos ),
    vel( dir * speed )
{}
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
float Bullet::GetDamege() const
{
    return damege;
}
