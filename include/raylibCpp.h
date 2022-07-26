#pragma once
#include "raylib.h"
#include "Settings.h"
#include <vector>
#include "Rect.h"
#include "Vec2.h"

namespace rayCpp
{
    void DrawSprite(const Texture2D& s, const Vec2& pos, const RectI& srcRect);
    void DrawSprite(const Texture2D& s, const Vec2& pos, const RectI& srcRect, float scale);
    void DrawSprite(const Texture2D& s, const Vec2& pos, const RectI& srcRect, Color color);
    void DrawSprite(const Texture2D& s, const Vec2& pos, const RectI& srcRect, const RectI& dest, const Vec2& origin, const float rotation, Color color);
    void DrawRectThin(const RectI& rect, const Color& color);

    RectI GetScreenRect();

    template <typename V>
    inline void remove_element(std::vector<V>& vec, size_t index )
    {
        std::swap( vec[index], vec.back() );
        vec.pop_back();
    }
}