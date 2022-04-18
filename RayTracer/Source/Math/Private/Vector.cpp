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

Vec3 Vec3::GetRandomPointInUnitDisk()
{
    Vec3 point;
    bool has_found_point = false;
    while (has_found_point == false)
    {
        point = Vec3(RandRange(-1.0f, 1.0f), RandRange(-1.0f, 1.0f), 0.0f);
        has_found_point = point.LengthSquared() < 1.0f;
    }

    return point;
}

Vec3 Vec3::GetRandomUnitVector()
{
    return Normalize(GetRandomPointInUnitSphere());
}

Vec3 Vec3::Reflect(const Vec3& v, const Vec3& n)
{
    // We basically project v onto n, multiply it by 2 and subtract it from v, because v points in.
    // n is a unit vector, so we can save the division operation in the projection.
    // Good recap for this: https://www.youtube.com/watch?v=naaeH1qbjdQ
    return v - 2.0f * Dot(v, n) * n;
}

Vec3 Vec3::Refract(const Vec3& v, const Vec3& n, const float etai_over_etat)
{
    // For implementation details and info about the underlying math check out
    // https://raytracing.github.io/books/RayTracingInOneWeekend.html#dielectrics/snell'slaw
    float cos_theta = fminf(Dot(-v, n), 1.0f);  // Simply the dot product here, because we assume v and n to be unit vectors
    Vec3 refracted_dir_perpendicular = etai_over_etat * (v + cos_theta * n);
    Vec3 refracted_dir_parallel = -sqrtf(fabsf(1.0f - refracted_dir_perpendicular.LengthSquared())) * n;
    return refracted_dir_perpendicular + refracted_dir_parallel;
}

float Vec3::Length() const
{
    return sqrtf(LengthSquared());
}

float Vec3::LengthSquared() const
{
    return x_ * x_ + y_ * y_ + z_ * z_;
}

bool Vec3::IsZero(float tolerance) const
{
    return (fabsf(x_) < tolerance && fabsf(y_) < tolerance && fabsf(z_) < tolerance);
}
