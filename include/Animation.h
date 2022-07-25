#pragma once
#include <vector>
#include "raylibCpp.h"

class Animation
{
public:
    Animation(int x, int y, int width, int height, int count, const Texture2D& sprite, float holdTime);
    void Update( float dTime );
    void Update( float dTime, const Sound& sound, const int nFramePerSound );
    void Advance();
    void Advance(const Sound& sound, const int nFramePerSound);
    template <typename E>
    void Draw( const Vec2& pos, E effect ) const
    {
        Draw( pos, frames[iCurFrame], effect );
    }
    template <typename E>
    void Draw( const Vec2& pos, const RectI& dest, E effect ) const
    {
        Rectangle srcRect = frames[iCurFrame].rayRect();
        Rectangle destRect = dest.rayRect();
        effect(
            *sprite, pos, srcRect, destRect
        );
    }
private:
    const Texture2D* sprite;
    std::vector<RectI> frames;
    int iCurFrame = 0;
    float curFrameTime = 0.0f;
    float holdTime;
};