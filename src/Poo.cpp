#include "Poo.h"
#include "SpriteEffects.h"
#include <iostream>

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
    effState = src.effState;
    return *this;
}
void Poo::SetDirection( const Vec2& dir )
{
    if(effState != EffectState::Dying)
        vel = dir * speed;
    else
        vel = { 0.0f, 0.0f };
}
void Poo::AdjustPos( float dTime )
{
    pos -= vel * dTime;
}
void Poo::ApplyDamege( const float damege )
{
    hp -= (int)damege;

    if(hp <= 0)
        effState = EffectState::Dying;
    else
        effState = EffectState::Hurt;
}
bool Poo::IsDead() const
{
    return effState == EffectState::Dead;
}
void Poo::Update( float dTime )
{
    pos += vel * dTime;

    if(effState != lastState)
    {
        effectCurrent = 0.0f;
    }
    else
    {
        if(effState != EffectState::Normal) effectCurrent += dTime;
    }

    if(effState == EffectState::Hurt)     // Be Hit
    {
        if(effectCurrent > duraHurtEff)
        {
            effState = EffectState::Normal;
        }
    }
    else if( effState == EffectState::Dying )        // Be Die
    {
        if(effectCurrent > duraDyingEff)
        {
            effState = EffectState::Dead;
        }
    }

    lastState = effState;
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
    //Process before switch
    const Vec2 draw_pos = pos + draw_offset;
    unsigned char a = 255 - (effectCurrent / duraDyingEff) * 255;   // chroma Effect Dying

    switch (effState)
    {
    case Poo::EffectState::Normal:
        rayCpp::DrawSprite(sprite, draw_pos, RectI{{0, 0}, sprite.width, sprite.height });
        break;
    case Poo::EffectState::Hurt:
        rayCpp::DrawSprite(sprite, draw_pos, RectI{{0, 0}, sprite.width, sprite.height }, RED);
        break;
    case Poo::EffectState::Dying:
        rayCpp::DrawSprite(sprite, draw_pos, RectI{{0, 0}, sprite.width, sprite.height }, { 255, 255, 255, a });
        break;
    default:
        break;
    }
}