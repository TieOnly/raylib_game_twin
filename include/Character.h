#pragma once
#include "raylibCpp.h"
#include <vector>
#include "Animation.h"
#include "Codex.h"

class Character
{
private:
    class DamegeEffectController
    {
    public:
        DamegeEffectController(Character& parent);
        void Update( float dTime );
        void Active();
        bool IsActive() const;
        void Draw() const;
    private:
        Character& parent;
        float time;
        bool active = false;
        static constexpr float totalDuration = 1.5f;
        static constexpr float RedDuration = 0.1f;
        static constexpr float blinkHalfPeriod = 0.16f;
    };

private:
    enum class AnimationSequence
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
    void SetDirection( const Vec2& dir );
    void AdjustPos(float dTime);
    void ApplyEffect();
    bool IsInvisible() const;
    void Update( float dTime );
    const Vec2& GetPos();
    void Draw() const;
    RectI GetHitBox() const;

private:
    const Texture2D* sprite;
    Vec2 pos;
    Vec2 vel = { 0.0f, 0.0f };
    static constexpr float speed = 180.0f;
    Vec2 draw_offset = { -45.0f, -64.0f };
    static constexpr int hwHitBox = 14;
    static constexpr int hhHitBox = 10;

    std::vector<Animation> animations;
    AnimationSequence iCurAnimationSequence = AnimationSequence::StandingDown;
    Sound stepSound;
    int nFramePerSound = 2;

    DamegeEffectController dec = { *this };
};