#pragma once
#include "Source/Math/Public/Vector.h"

struct Ray
{
    Ray();
    Ray(const Point3 origin, const Vec3 direction);

    /**
    *   Calculates position of ray parameterized by f, i.e. p = origin_+ f * direction_
    *   @param f    How far along the direction_ vector we go
    *   @return    The position of the ray if we go "f steps" from its origin into its direction.
    */
    Point3 At(float f) const;

    Point3 origin_;
    Vec3 direction_;
};
