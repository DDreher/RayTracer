#include "Vector.h"

const Vec3 Vec3::WHITE = Vec3(1.0f, 1.0f, 1.0f);
const Vec3 Vec3::BLACK = Vec3(0.0f, 0.0f, 0.0f);

Vec3 Vec3::operator-() const
{
    return Vec3(-x_, -y_, -z_);
}

float Vec3::operator[](int i) const
{
    return data_[i];
}

float& Vec3::operator[](int i)
{
    return data_[i];
}

Vec3& Vec3::operator+=(const Vec3& v)
{
    data_[0] += v.data_[0];
    data_[1] += v.data_[1];
    data_[2] += v.data_[2];
    return *this;
}

Vec3& Vec3::operator*=(const float f)
{
    data_[0] *= f;
    data_[1] *= f;
    data_[2] *= f;
    return *this;
}

Vec3& Vec3::operator/=(const float f)
{
    return *this *= 1 / f;
}

Vec3& Vec3::operator/=(const uint32 i)
{
    float scale = 1.0f / i;
    x_ *= scale;
    y_ *= scale;
    z_ *= scale;

    return *this;
}

Vec3 Vec3::Random()
{
    return Vec3(Rand(), Rand(), Rand());
}

Vec3 Vec3::Random(float min, float max)
{
    return Vec3(RandRange(min, max), RandRange(min, max), RandRange(min, max));
}

Point3 Vec3::GetRandomPointInUnitSphere()
{
    bool found_point = false;
    Point3 p;

    // We just get random points until we find
    while (found_point == false)
    {
        p = Vec3::Random(-1.0f, 1.0f);
        // If the distance from the origin of the sphere to the point is less than 1 we know that it's inside the unit sphere
        found_point = p.LengthSquared() < 1.0f;
    }

    return p;
}

Vec3 Vec3::GetRandomUnitVector()
{
    return MakeUnitVec(GetRandomPointInUnitSphere());
}

float Vec3::Length() const
{
    return sqrtf(LengthSquared());
}

float Vec3::LengthSquared() const
{
    return x_ * x_ + y_ * y_ + z_ * z_;
}
