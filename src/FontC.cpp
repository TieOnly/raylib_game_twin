#include "FontC.h"
#include "assert.h"

FontC::FontC( const std::string& fileName )
    :
    surf( Codex::Retrieve( fileName ) ),
    glyphWidth( surf->width / colums ),
    glyphHeight( surf->height / rows )
{
    assert( glyphWidth * colums == surf->width );
    assert( glyphHeight * rows == surf->height );
}
RectI FontC::MapGlyphRectI( char c ) const
{
    assert( c >= fisrtChar && c <= lastChar );

    const int glyphIndex = c - ' ';

    const int xGlyph = glyphIndex % colums; 
    const int yGlyph = glyphIndex / colums;

    return RectI{ {xGlyph * glyphWidth, yGlyph * glyphHeight}, glyphWidth, glyphHeight }; 

}
void FontC::DrawText( const std::string& text, const Vei2& pos, Color color )
{
    Vei2 curPos = pos;
    for( char c : text )
    {
        if(c == '\n')
        {
            curPos.x = pos.x;
            curPos.y += glyphHeight;
            continue;
        }
        else if(c >= fisrtChar + 1 && c <= lastChar)
        {
            rayCpp::DrawSprite( *surf, (Vec2)curPos, MapGlyphRectI( c ), color );
        }
        curPos.x += glyphWidth;
    }
}