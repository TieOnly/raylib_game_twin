#pragma once
#include "raylibCpp.h"
#include "Rect.h"
#include "Vec2.h"
#include <string>
#include "Codex.h"
#include <iostream>
class BackGround
{
public:
    BackGround(const Vec2 origin_in, const std::string& map1, const std::string& map2)
        :
        lay1( Codex::Retrieve( "../assets/img/ground.png" ) ),
        lay2( Codex::Retrieve( "../assets/img/wall.png" ) ),
        origin( origin_in )
    {
        tiles.reserve( gridDimens );
        {
            auto m1 = map1.cbegin();
            auto m2 = map2.cbegin();
            for(int iY = 0; iY < gridHeight; iY++)
            {
                for(int iX = 0; iX < gridWidth; iX++, ++m1, ++m2)
                {
                    if(*m2 - 'B' > 0)
                    {
                        tiles.push_back( *m2 - 'B' );    //B = 0, C = 1, A = -1
                        boundary.emplace_back( RectI{ {int(iX * tileW), int(iY * tileH)}, (int)tileW, (int)tileH } );
                    }
                    else
                    {
                        tiles.push_back( *m1 - 'B' );    //B = 0, C = 1, A = -1
                    }
                }
            }
        }
    }
    bool IsBoundaryWith( const RectI& target ) const
    {
        for( size_t i = 0u; i < boundary.size(); ++i)
        {
            if( boundary[i].IsOverLapping( target ) )
            {
                return 1;
            }
        }
        return 0;
    }
    void Draw() const
    {
        for(int iY = 0; iY < gridHeight; ++iY)
        {
            for(int iX = 0; iX < gridWidth; ++iX)
            {
                const int tile = GetTileAt( iX, iY );
                if( tile > 0 )
                {
                    Rectangle srcRect = Rectangle{ 0.0f, 0.0f, (float)lay2->width, (float)lay2->height};
                    Rectangle destRect = Rectangle{ 
                        origin.x + float(iX * tileW), 
                        origin.y + float(iY * tileH), 
                        (float)tileW, 
                        (float)tileH
                        };

                    DrawTexturePro(*lay2, srcRect, destRect, {0.0f, 0.0f}, 0.0f, WHITE);
                }
                else
                {
                    Rectangle srcRect = Rectangle{ 0.0f, 0.0f, (float)lay1->width, (float)lay1->height};
                    Rectangle destRect = Rectangle{ 
                        origin.x + float(iX * tileW), 
                        origin.y + float(iY * tileH), 
                        (float)tileW, 
                        (float)tileH
                        };

                    DrawTexturePro(*lay1, srcRect, destRect, {0.0f, 0.0f}, 0.0f, WHITE);
                }
            }
        }
    }
    int GetTileAt( const int x, const int y ) const
    {
        return tiles[y * gridWidth + x];
    }
private:
    const Texture2D* lay1;
    const Texture2D* lay2;
    Vec2 origin;    //topleft
    static constexpr int gridWidth = 10;
    static constexpr int gridHeight = 10;
    static constexpr int gridDimens = gridWidth * gridHeight;
    static constexpr float tileW = settings::screenW / gridWidth;
    static constexpr float tileH = settings::screenH / gridHeight;
    std::vector<int> tiles;
    std::vector<RectI> boundary;
};