#pragma once
#include "Source/Math/Public/Vector.h"

struct Ray
{
    Ray();
    Ray(const Point3 origin, const Vec3 direction);

    Point3 GetOrigin() const;
    Vec3 GetDirection() const;

    Point3 At(float f) const;

    Point3 origin_;
    Vec3 direction_;
};
