#include "Source/Math/Public/Vector.h"

const Vec3 Vec3::WHITE = Vec3(1.0f, 1.0f, 1.0f);

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

float Vec3::Length() const
{
    return sqrtf(LengthSquared());
}

float Vec3::LengthSquared() const
{
    return x_ * x_ + y_ * y_ + z_ * z_;
}
