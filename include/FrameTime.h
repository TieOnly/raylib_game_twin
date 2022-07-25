#pragma once
#include <chrono>

class FrameTime
{
public:
    FrameTime();
    float Mark();
private:
    std::chrono::steady_clock::time_point last;
};