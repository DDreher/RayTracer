#include "Ray.h"

Ray::Ray()
{
}

Ray::Ray(const Point3 origin, const Vec3 direction)
    : origin_(origin), direction_(direction)
{
}

Point3 Ray::At(float f) const
{
    return origin_ + f * direction_;
}
