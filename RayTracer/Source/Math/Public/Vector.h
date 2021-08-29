#pragma once
#include "cmath"

struct Vec3
{
    Vec3() {};
    Vec3(float x, float y, float z) : x_(x), y_(y), z_(z) {};

    Vec3 operator-() const;
    float operator[](int i) const;
    float& operator[](int i);
    Vec3& operator+=(const Vec3& v);
    Vec3& operator*=(const float f);
    Vec3& operator/=(const float f);
    Vec3& operator/=(const uint32 i);

    /**
    *    Get a random vector in range [0.0f, 1.0f)
    *    
    *    @return the random vector
    */
    static Vec3 Random();

    /**
    *    Get a random vector in range [min, max)
    *    
    *    @param min the lower bound of the range
    *    @param max the upper bound of the range
    *    @return the random vector
    */
    static Vec3 Random(float min, float max);

    /**
    *    Get a random point in a unit sphere.
    *    The position is calculated using a rejection method.
    *    
    *    @return The calculated point
    */
    static Vec3 GetRandomPointInUnitSphere();

    /**
    *    Get a random point in a unit disk.
    *    The position is calculated using a rejection method.
    *
    *    @return The calculated point
    */
    static Vec3 GetRandomPointInUnitDisk();

    /**
    *    Get the vector to a random point inside a unit sphere using a rejection method.
    *    Once a vector is found, it's normalized.
    *    
    *    @return A random unit vector.
    */
    static Vec3 GetRandomUnitVector();

    /**
    *    Reflects a vector along a given normal.
    *    
    *    @param v   The vector to be reflected
    *    @param n   The unit normal the vector is reflected along
    *    @return The reflected vector
    */
    static Vec3 Reflect(const Vec3& v, const Vec3& n);

    /**
    *    Refracts a vector according to Snell's law.
    *
    *    @param v   The unit vector to be refracted
    *    @param n   The unit normal the vector is refrected along
    *    @param etai_over_etat  Ratio between eta_t and eta_t, i.e. the refraction indices of the two materials the ray passes through
    *    @return The refracted vector
    */
    static Vec3 Refract(const Vec3& v, const Vec3& n, const float etai_over_etat);

    float Length() const;
    float LengthSquared() const;

    /**
    *    Checks if a vector is (nearly) zero.
    *    
    *    @param tolerance   The tolerance under which the element is assumed to be zero
    *    @return True if all elements of a vector are below the given tolerance.
    */
    bool IsZero(float tolerance = SMALL_NUMBER) const;

public:
    static const Vec3 WHITE;
    static const Vec3 BLACK;

    union
    {
        float data_[3] = { 0.0f, 0.0f, 0.0f };
        struct 
        {
            float x_;
            float y_;
            float z_;
        };
    };
};

// Utility functions
inline Vec3 operator+(const Vec3& a, const Vec3& b)
{
    return Vec3(a.data_[0] + b.data_[0], a.data_[1] + b.data_[1], a.data_[2] + b.data_[2]);
}

inline Vec3 operator-(const Vec3& a, const Vec3& b)
{
    return Vec3(a.data_[0] - b.data_[0], a.data_[1] - b.data_[1], a.data_[2] - b.data_[2]);
}

inline Vec3 operator*(const Vec3& a, const Vec3& b)
{
    return Vec3(a.data_[0] * b.data_[0], a.data_[1] * b.data_[1], a.data_[2] * b.data_[2]);
}

inline Vec3 operator*(float f, const Vec3& v)
{
    return Vec3(f * v.data_[0], f * v.data_[1], f * v.data_[2]);
}

inline Vec3 operator*(const Vec3& v, float f)
{
    return f * v;
}

inline Vec3 operator/(Vec3 v, float f)
{
    return (1.0f / f) * v;
}

inline float Dot(const Vec3& a, const Vec3& b)
{
    return a.data_[0] * b.data_[0]
        + a.data_[1] * b.data_[1]
        + a.data_[2] * b.data_[2];
}

inline Vec3 Cross(const Vec3& a, const Vec3& b)
{
    return Vec3(a.data_[1] * b.data_[2] - a.data_[2] * b.data_[1],
        a.data_[2] * b.data_[0] - a.data_[0] * b.data_[2],
        a.data_[0] * b.data_[1] - a.data_[1] * b.data_[0]);
}

inline Vec3 MakeUnitVec(Vec3 v)
{
    return v / v.Length();
}

inline std::ostream& operator<<(std::ostream& output_stream, const Vec3& v)
{
    return output_stream << v.data_[0] << ' ' << v.data_[1] << ' ' << v.data_[2];
}

// Type aliases
using Point3 = Vec3;
using Color = Vec3; // RGB color
