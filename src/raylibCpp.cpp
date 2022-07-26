#include "raylibCpp.h"

void rayCpp::DrawSprite(const Texture2D& s, const Vec2& pos, const RectI& srcRect)
{
    DrawSprite(s, pos, srcRect, RectI{ (Vei2)pos, srcRect.width, srcRect.height }, { 0.0f, 0.0f }, 0.0f, WHITE);
}
void rayCpp::DrawSprite(const Texture2D& s, const Vec2& pos, const RectI& srcRect, float scale)
{
    DrawSprite(s, pos, srcRect, RectI{ (Vei2)pos, int(srcRect.width*scale), int(srcRect.height*scale) }, { 0.0f, 0.0f }, 0.0f, WHITE);
}
void rayCpp::DrawSprite(const Texture2D& s, const Vec2& pos, const RectI& srcRect, Color color)
{
    DrawSprite(s, pos, srcRect, RectI{ (Vei2)pos, srcRect.width, srcRect.height }, { 0.0f, 0.0f }, 0.0f, color);
}
void rayCpp::DrawSprite(const Texture2D& s, const Vec2& pos, const RectI& srcRect, const RectI& dest, const Vec2& origin, const float rotation, Color color)
{
    // Rectangle rSrc = srcRect.rayRect();
    // Rectangle dSrc = dest.rayRect();
    // Vector2 ori = { origin.x, origin.y };

    DrawTexturePro(s, srcRect.rayRect(), dest.rayRect(), { origin.x, origin.y }, rotation, color);
}
void rayCpp::DrawRectThin(const RectI& rect, const Color& color)
{
    // DrawRectangle( rect.left, rect.top, rect.width, rect.height, color );
    Rectangle rayRect = rect.rayRect();
    DrawRectangleLinesEx( rayRect, 2.0f, color );
}
RectI rayCpp::GetScreenRect(  )
{
    // return RectI{ {0, 0}, GetScreenWidth(), GetScreenHeight() };
    return RectI{ {0, 0}, settings::screenW, settings::screenH };
}
