#pragma once
#include <cmath>
#include <limits>
#include <random>
#include <stdlib.h>

//~ Constants
#define SMALL_NUMBER (1.e-8f)
static inline const float FLOAT_INF = std::numeric_limits<float>::infinity();
static inline const float PI = 3.1415926535897932f;

//~ Utility functions
inline float DegToRads(float degrees)
{
    return degrees * PI / 180.0f;
}

/** Returns a random float in range [0.0, 1.0] */
inline float Rand()
{
    // See: https://stackoverflow.com/questions/60450514/safe-random-number-generation-using-rand-or-stdrandom-device-in-c
    thread_local std::random_device random_device;
    thread_local std::mt19937 rng(random_device());
    thread_local std::uniform_real_distribution<float> distribution;
    return distribution(rng, decltype(distribution)::param_type{ 0.0f, 1.0f });
}

/** Returns a random float in range [min, max] */
inline float RandRange(float min, float max)
{
    return min + (max - min) * Rand();
}

/** Clamps a given value v to range [min, max] */
template <typename T>
inline T Clamp(T v, T min, T max)
{
    if (v < min) { return min; }
    else if (v > max) { return max; }
    else { return v; }
}

/**
*    Checks if a float is (nearly) zero.
*
*    @param tolerance   The tolerance under which the float is assumed to be zero
*    @return True if the float f is below given tolerance.
*/
inline bool IsNearlyZero(float f, float tolerance = SMALL_NUMBER)
{
    return fabsf(f) < tolerance;
}
