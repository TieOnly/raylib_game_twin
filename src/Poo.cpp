#include "Poo.h"
#include "SpriteEffects.h"

Poo::Poo( const Vec2& pos )
    :
    sprite( LoadTexture("../assets/img/poo.png") ),
    pos( pos )
{
    
}
void Poo::SetDirection( const Vec2& dir )
{
    vel = dir * speed;
}
void Poo::ActivateEffect()
{
    isEffect = true;
    effectCurrent = 0.0f;
}
void Poo::Update( float dTime )
{
    pos += vel * dTime;
    if(isEffect)
    {
        effectCurrent += dTime;
        if(effectCurrent >= effectTime)
        {
            isEffect = false;
        }
    }
}
const Vec2& Poo::GetPos()
{
    return pos;
}
RectI Poo::GetHitBox() const
{
    return RectI::FromCenter( (Vei2)pos, hwHitBox, hhHitBox );
}
void Poo::Draw() const
{
    const Vec2 draw_pos = pos + draw_offset;

    if(isEffect)
    {
        rayCpp::DrawSprite(sprite, draw_pos, RectI{{0, 0}, sprite.width, sprite.height }, RED);
    }
    else
    {
        rayCpp::DrawSprite(sprite, draw_pos, RectI{{0, 0}, sprite.width, sprite.height });
    }
}