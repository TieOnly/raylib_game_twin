#pragma once
#include "raylibCpp.h"
#include <vector>
#include "Animation.h"

class Poo
{
public: 
    Poo( const Vec2& pos );
    void ProcessControl();
    void SetDirection( const Vec2& dir );
    void ActivateEffect();
    void Update( float dTime );
    const Vec2& GetPos();
    RectI GetHitBox() const;
    void Draw() const;

private:
    const Texture2D sprite;
    Vec2 pos;
    Vec2 vel = { 0.0f, 0.0f };
    static constexpr float speed = 110.0f;
    Vec2 draw_offset = { -16.0f, -20.0f };
    static constexpr int hwHitBox = 12;
    static constexpr int hhHitBox = 6;

    Sound stepSound;
    int nFramePerSound = 2;
    static constexpr float effectTime = 0.1f;
    float effectCurrent = 0.0f;
    bool isEffect = false;
};