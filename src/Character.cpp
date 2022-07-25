#include "Character.h"
#include "SpriteEffects.h"

Character::Character( const Vec2& pos )
    :
    sprite( LoadTexture("../assets/img/elf.png") ),
    pos( pos ),
    stepSound( LoadSound("../assets/audio/step.mp3") )
{
    for(int i = 0; i < (int)Sequence::StandingLeft; i++)
    {
        animations.emplace_back( Animation( 90, 90*i, 90, 90, 4, sprite, 0.16f ) );
    }
    for(int i = (int)Sequence::StandingLeft; i < (int)Sequence::Count; i++)
    {
        animations.emplace_back( Animation( 0, 90*(i - (int)Sequence::StandingLeft), 90, 90, 1, sprite, 0.16f ) );
    }
}
void Character::ProcessControl()
{

}
void Character::SetDirection( const Vec2& dir )
{
    if( dir.x > 0)
    {
        iCurSequence = Sequence::WalkingRight;
    }
    else if ( dir.x < 0 )
    {
        iCurSequence = Sequence::WalkingLeft;
    }
    else if ( dir.y > 0 )
    {
        iCurSequence = Sequence::WalkingDown;
    }
    else if ( dir.y < 0 )
    {
        iCurSequence = Sequence::WalkingUp;
    }
    else
    {
        if(vel.x > 0)
        {
            iCurSequence = Sequence::StandingRight;
        }
        else if( vel.x < 0 )
        {
            iCurSequence = Sequence::StandingLeft;
        }
        else if( vel.y > 0 )
        {
            iCurSequence = Sequence::StandingDown;
        }
        else if( vel.y < 0 )
        {
            iCurSequence = Sequence::StandingUp;
        }
    }
    vel = dir * speed;
}
void Character::ActivateEffect()
{
    isEffect = true;
    effectCurrent = 0.0f;
}
void Character::Update( float dTime )
{
    pos += vel * dTime;
    if(vel != 0)
    {
        animations[(int)iCurSequence].Update( dTime, stepSound, nFramePerSound );
    }
    else
    {
        animations[(int)iCurSequence].Update( dTime );
    }
    if(isEffect)
    {
        effectCurrent += dTime;
        if(effectCurrent >= effectTime)
        {
            isEffect = false;
        }
    }
}
const Vec2& Character::GetPos()
{
    return pos;
}
RectI Character::GetHitBox() const
{
    return RectI::FromCenter( (Vei2)pos, hwHitBox, hhHitBox );
}
void Character::Draw() const
{
    const Vec2 draw_pos = pos + draw_offset;

    if(isEffect)
    {
        SpriteEffects::Chroma e{ RED };
        animations[(int)iCurSequence].Draw( draw_pos, e );
    }
    else
    {
        SpriteEffects::Chroma e{ WHITE };
        animations[(int)iCurSequence].Draw( draw_pos, e );
    }
}