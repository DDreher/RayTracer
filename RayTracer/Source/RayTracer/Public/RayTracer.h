#pragma once
#include "Ray.h"
#include "Hittable.h"

struct RayTracer
{
    static Color CalcRayColor(const Ray& r, const IHittable& scene_objects);
};
