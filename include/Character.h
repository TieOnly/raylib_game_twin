#pragma once
#include "raylibCpp.h"
#include <vector>
#include "Animation.h"

class Character
{
private:
    enum class Sequence
    {
        WalkingLeft,
        WalkingRight,
        WalkingUp,
        WalkingDown,
        StandingLeft,
        StandingRight,
        StandingUp,
        StandingDown,
        Count
    };
public: 
    Character( const Vec2& pos );
    void ProcessControl();
    void SetDirection( const Vec2& dir );
    void ActivateEffect();
    void Update( float dTime );
    const Vec2& GetPos();
    void Draw() const;
    RectI GetHitBox() const;

private:
    const Texture2D sprite;
    Vec2 pos;
    Vec2 vel = { 0.0f, 0.0f };
    static constexpr float speed = 180.0f;
    Vec2 draw_offset = { -45.0f, -64.0f };
    static constexpr int hwHitBox = 14;
    static constexpr int hhHitBox = 10;

    std::vector<Animation> animations;
    Sequence iCurSequence = Sequence::StandingDown;
    Sound stepSound;
    int nFramePerSound = 2;
    static constexpr float effectTime = 0.1f;
    float effectCurrent = 0.0f;
    bool isEffect = false;
};