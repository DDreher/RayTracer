#pragma once
#include <cmath>
#include <limits>

//~ Constants
static inline const float INF = std::numeric_limits<float>::infinity();
static inline const float PI = 3.1415926535897932f;

//~ Utility functions
inline float DegToRads(float degrees)
{
    return degrees * PI / 100.0f;
}
