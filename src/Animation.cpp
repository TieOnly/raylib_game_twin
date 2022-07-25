#include "Animation.h"

Animation::Animation(int x, int y, int width, int height, int count, const Texture2D& sprite, float holdTime)
    :
    sprite( sprite ),
    holdTime( holdTime )
{
    for(int i = 0; i < count; i++)
    {
        frames.emplace_back( x + i * width, x + (i + 1) * width, y, y + height );
    }
}
void Animation::Update( float dTime )
{
    curFrameTime += dTime;
    while( curFrameTime >= holdTime )
    {
        Advance();
        curFrameTime -= holdTime;
    }
}
void Animation::Advance()
{
    if( ++iCurFrame >= (int)frames.size() )
    {
        iCurFrame = 0;
    }
}
void Animation::Update( float dTime, const Sound& sound, const int FramePerSound )
{
    curFrameTime += dTime;
    while( curFrameTime >= holdTime )
    {
        Advance(sound, FramePerSound);
        curFrameTime -= holdTime;
    }
}
void Animation::Advance(const Sound& sound, const int FramePerSound)
{
    if( iCurFrame % FramePerSound == 0)
    {
        PlaySound(sound);
    }
    if( ++iCurFrame >= (int)frames.size() )
    {
        iCurFrame = 0;
    }
}
