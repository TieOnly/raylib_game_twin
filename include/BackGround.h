#pragma once
#include "raylibCpp.h"
#include "Rect.h"
#include "Vec2.h"

class BackGround
{
public:
    BackGround(const Texture2D& surf_in, const Vec2 origin_in)
        :
        surf( surf_in ),
        origin( origin_in )
    {}
    void Draw() const
    {
        for(int iY = 0; iY < gridHeight; ++iY)
        {
            for(int iX = 0; iX < gridWidth; ++iX)
            {
                Rectangle srcRect = Rectangle{ 0.0f, 0.0f, (float)surf.width, (float)surf.height};
                Rectangle destRect = Rectangle{ 
                    origin.x + float(iX * tileW), 
                    origin.y + float(iY * tileH), 
                    (float)tileW, 
                    (float)tileH
                    };

                DrawTexturePro(surf, srcRect, destRect, {0.0f, 0.0f}, 0.0f, WHITE);
            }
        }
    }
private:
    Texture2D surf;
    Vec2 origin;    //topleft
    static constexpr int gridWidth = 10;
    static constexpr int gridHeight = 10;
    static constexpr float tileW = settings::screenW / gridWidth;
    static constexpr float tileH = settings::screenH / gridHeight;
};