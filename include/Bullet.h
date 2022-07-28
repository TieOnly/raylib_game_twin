#pragma once
#include "raylibCpp.h"
#include "Animation.h"
#include "Codex.h"

class Bullet
{
public:
    Bullet( const Vec2& pos, const Vec2& dir);
    void Update( float dTime );
    void Draw() const;
    const Vec2& GetPos() const;
    RectI GetHitBox() const;
    float GetDamege() const;
private:
    const Texture2D* bullet_surf;
    Animation bullet_animation;
    Vec2 pos;
    Vec2 vel = { 0.0f, 0.0f };
    static constexpr float speed = 100.0f;
    static constexpr Vec2 draw_offset = { -12.0f, -12.0f };
    static constexpr float hwHitBox = 12.0f;
    static constexpr float hhHitBox = 12.0f;
    static constexpr float damege = 30.0f;
};