#pragma once
#include "raylib.h"
#include "Vec2.h"

template <typename T>
class Rect_
{
public:
    Rect_() = default;
    Rect_(T left_in, T right_in, T top_in, T bottom_in)
        :
        left(left_in),
        right(right_in),
        top(top_in),
        bottom(bottom_in)
    {}
    Rect_(const Vec2_<T>& topLeft, const Vec2_<T>& bottomRight)
        :
        Rect_(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
    {}
    Rect_(const Vec2_<T>& topLeft, const T& width, const T& height)
        :
        Rect_(topLeft, topLeft + Vec2_<T>{width, height})
    {}
    static Rect_ FromCenter(const Vec2_<T>& center, const T halfWidth, const T halfHeight)
    {
        return Rect_{ center - Vec2_<T>{ halfWidth, halfHeight }, center + Vec2_<T>{ halfWidth, halfHeight }};
    }
    bool IsOverLapping(const Rect_& other) const
    {
        return right > other.left && bottom > other.top 
            && left < other.right && top < other.bottom;
    }
    Rectangle rayRect() const
    {
        return Rectangle{ (float)left, (float)top, (float)(right - left), (float)(bottom - top)};
    }
    Vec2_<T> GetCenter() const
    {
        return Vec2_<T>{ left + (width/2), top + (height/2) };
    }
public:
    T left;
    T right;
    T top;
    T bottom;
    T width = right - left;
    T height = bottom - top;
};

typedef Rect_<int> RectI;
typedef Rect_<float> RectF;
