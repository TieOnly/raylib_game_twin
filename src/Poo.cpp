#include "Poo.h"
#include "SpriteEffects.h"

Poo::Poo( const Texture2D& sprite_in, const Vec2& pos )
    :
    sprite( sprite_in ),
    pos( pos )
{
    
}
Poo::Poo( const Poo& src )
    :
    sprite( src.sprite ),
    pos( src.pos )
{}
Poo& Poo::operator = ( const Poo& src )
{
    pos = src.pos;
    hp = src.hp;
    isEffect = src.isEffect;
    return *this;
}
void Poo::SetDirection( const Vec2& dir )
{
    vel = dir * speed;
}
void Poo::ApplyDamege( const float damege )
{
    hp -= damege;
    isEffect = true;
    effectCurrent = 0.0f;
}
bool Poo::IsDead() const
{
    return hp <= 0.0f;
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

    if(!IsDead())
    {
        if(isEffect)
        {
            rayCpp::DrawSprite(sprite, draw_pos, RectI{{0, 0}, sprite.width, sprite.height }, RED);
        }
        else
        {
            rayCpp::DrawSprite(sprite, draw_pos, RectI{{0, 0}, sprite.width, sprite.height });
        }
    }
}