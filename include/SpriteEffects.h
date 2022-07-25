#pragma once
#include "raylibCpp.h"

namespace SpriteEffects
{

    class Chroma
    {
    public:
        Chroma(Color c)
            :
            chroma( c )
        {}
        void operator()( const Texture2D& sprite, const Vec2& pos, const Rectangle& srcRect, const Rectangle& dest)
        {
            DrawTexturePro(
                sprite, srcRect, 
                { pos.x, pos.y, fabsf(dest.width), fabsf(dest.height) }, 
                {0.0f, 0.0f}, 0.0f, chroma
            );
        }
    private:
        Color chroma;
    };

};