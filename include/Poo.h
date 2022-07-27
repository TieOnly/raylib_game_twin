#pragma once
#include "raylibCpp.h"
#include <vector>
#include "Animation.h"

class Poo
{
private:
    enum class EffectState
    {
        Dead,
        Dying,
        Hurt,
        Normal
    };
public: 
    Poo( const Texture2D& sprite_in, const Vec2& pos );
    Poo( const Poo& src );
    Poo& operator = ( const Poo& src );
    void SetDirection( const Vec2& dir );
    void AdjustPos(float dTime);
    void ApplyDamege( const float damege );
    bool IsDead() const;
    void Update( float dTime );
    const Vec2& GetPos();
    RectI GetHitBox() const;
    void Draw() const;

private:
    const Texture2D sprite;
    Vec2 pos;
    Vec2 vel = { 0.0f, 0.0f };
    static constexpr float speed = 50.0f;
    Vec2 draw_offset = { -16.0f, -20.0f };
    static constexpr int hwHitBox = 12;
    static constexpr int hhHitBox = 6;

    Sound stepSound;
    int nFramePerSound = 2;

    int hp = 100;
    EffectState effState = EffectState::Normal;
    EffectState lastState = effState;
    bool isChangeStated = false;
    static constexpr float duraHurtEff = 0.2f;
    static constexpr float duraDyingEff = 1.0f;
    float effectCurrent = 0.0f;

};