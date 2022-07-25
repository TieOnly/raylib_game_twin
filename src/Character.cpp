#include "Character.h"
#include "SpriteEffects.h"

Character::Character( const Vec2& pos )
    :
    sprite( LoadTexture("../assets/img/elf.png") ),
    pos( pos ),
    stepSound( LoadSound("../assets/audio/step.mp3") )
{
    for(int i = 0; i < (int)AnimationSequence::StandingLeft; i++)
    {
        animations.emplace_back( Animation( 90, 90*i, 90, 90, 4, sprite, 0.16f ) );
    }
    for(int i = (int)AnimationSequence::StandingLeft; i < (int)AnimationSequence::Count; i++)
    {
        animations.emplace_back( Animation( 0, 90*(i - (int)AnimationSequence::StandingLeft), 90, 90, 1, sprite, 0.16f ) );
    }
}
void Character::SetDirection( const Vec2& dir )
{
    if( dir.x > 0)
    {
        iCurAnimationSequence = AnimationSequence::WalkingRight;
    }
    else if ( dir.x < 0 )
    {
        iCurAnimationSequence = AnimationSequence::WalkingLeft;
    }
    else if ( dir.y > 0 )
    {
        iCurAnimationSequence = AnimationSequence::WalkingDown;
    }
    else if ( dir.y < 0 )
    {
        iCurAnimationSequence = AnimationSequence::WalkingUp;
    }
    else
    {
        if(vel.x > 0)
        {
            iCurAnimationSequence = AnimationSequence::StandingRight;
        }
        else if( vel.x < 0 )
        {
            iCurAnimationSequence = AnimationSequence::StandingLeft;
        }
        else if( vel.y > 0 )
        {
            iCurAnimationSequence = AnimationSequence::StandingDown;
        }
        else if( vel.y < 0 )
        {
            iCurAnimationSequence = AnimationSequence::StandingUp;
        }
    }
    vel = dir * speed;
}
void Character::ApplyEffect()
{
    dec.Active();
}
bool Character::IsInvisible() const
{
    return dec.IsActive();
}
void Character::Update( float dTime )
{
    pos += vel * dTime;
    if(vel != 0)
    {
        animations[(int)iCurAnimationSequence].Update( dTime, stepSound, nFramePerSound );
    }
    else
    {
        animations[(int)iCurAnimationSequence].Update( dTime );
    }
    dec.Update( dTime );
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
    dec.Draw();
}

///////////////////////////////////////////////////////////////////////
Character::DamegeEffectController::DamegeEffectController(Character& parent)
    :
    parent( parent )
{}
void Character::DamegeEffectController::Update( float dTime )
{
    if(active)
    {
        time += dTime;
        if(time >= totalDuration)
        {
            active = false;
        }
    }
}
void Character::DamegeEffectController::Active()
{
    if(!active)
    {
        active = true;
        time = 0.0f;
    }
}
bool Character::DamegeEffectController::IsActive() const
{
    return active;
}
void Character::DamegeEffectController::Draw() const
{
    const Vec2 draw_pos = parent.pos + parent.draw_offset;

    if(active)
    {
        if( time <= RedDuration )
        {
            SpriteEffects::Chroma e{ RED };
            parent.animations[(int)parent.iCurAnimationSequence].Draw( draw_pos, e );
        }
        else
        {
            if( int(time / blinkHalfPeriod) % 2 != 0 )
            {
                SpriteEffects::Chroma e{ WHITE };
                parent.animations[(int)parent.iCurAnimationSequence].Draw( draw_pos, e );
            }
        }
    }
    else
    {
        SpriteEffects::Chroma e{ WHITE };
        parent.animations[(int)parent.iCurAnimationSequence].Draw( draw_pos, e );
    }
}
