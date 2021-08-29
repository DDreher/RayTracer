#pragma once
#include <cmath>
#include <limits>
#include <stdlib.h>

//~ Constants
#define SMALL_NUMBER (1.e-8f)
static inline const float INF = std::numeric_limits<float>::infinity();
static inline const float PI = 3.1415926535897932f;

//~ Utility functions
static inline float DegToRads(float degrees)
{
    return degrees * PI / 100.0f;
}

/** Returns a random float in range [0, 1) */
static inline float Rand()
{
    return rand() / (RAND_MAX + 1.0f); 
}

/** Returns a random float in range [min, max) */
static inline float RandRange(float min, float max)
{
    return min + (max - min) * Rand();
}

static inline float Clamp(float f, float min, float max)
{
    if (f < min) { return min; }
    else if (f > max) { return max; }
    else { return f; }
}
