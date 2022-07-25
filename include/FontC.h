#pragma once
#include "raylibCpp.h"
#include "Rect.h"
#include <string>

class FontC
{
public:
    FontC( const std::string& fileName );
    void DrawText( const std::string& text, const Vei2& pos, Color color );

private:
    RectI MapGlyphRectI( char c ) const;

private:
    Texture2D surf;

    int glyphWidth; 
    int glyphHeight;

    static constexpr int colums = 32;
    static constexpr int rows = 3;

    static constexpr char fisrtChar = ' ';
    static constexpr char lastChar = '~';
};