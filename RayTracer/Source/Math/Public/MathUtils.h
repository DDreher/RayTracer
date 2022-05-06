#pragma once
#include <cmath>
#include <limits>
#include <random>
#include <stdlib.h>

#define GLM_FORCE_RADIANS   // Ensure that matrix functions use radians as units
#define GLM_ENABLE_EXPERIMENTAL // Needed so we can use the hash functions of GLM types
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // matrix functions like glm::lookAt etc.
#include <glm/gtc/random.hpp >
#include <glm/gtx/hash.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/transform.hpp>

using Vec2 = glm::vec2;
using Vec3 = glm::vec3;
using Vec4 = glm::vec4;
using Point3 = glm::vec3;
using Color = glm::vec3;
using Mat3 = glm::mat3;
using Mat4 = glm::mat4;

namespace colors
{
    static inline const Vec3 WHITE = Vec3(1.0f, 1.0f, 1.0f);
    static inline const Vec3 BLACK = Vec3(0.0f, 0.0f, 0.0f);
    static inline const Vec3 GOLD = Vec3(212.0f / 255.0f, 175.0f / 255.0f, 55.0f / 255.0f);
    static inline const Vec3 SILVER = Vec3(213.0f / 255.0f, 213.0f / 255.0f, 215.0f / 255.0f);
}

static Vec3 GetRandomUnitVector()
{
    return glm::normalize(glm::sphericalRand(1.0f));
}

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

/**
*    Checks if a Vec3 is (nearly) zero.
*
*    @param tolerance   The tolerance under which the float is assumed to be zero
*    @return True if the float f is below given tolerance.
*/
inline bool IsNearlyZero(Vec3 v, float tolerance = SMALL_NUMBER)
{
    return fabsf(v.x) < tolerance && fabsf(v.y) < tolerance && fabsf(v.z) < tolerance;
}
