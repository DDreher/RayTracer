#pragma once
#include "Ray.h"
#include "Hittable.h"
#include "Vector.h"

/**
*    Generic interface for materials which...
*    1) ... produce scattered rays (or absorb rays)
*    2) ... tell us how much a ray should be attenuated if it's scattered
*/
class IMaterial
{
public:
    /**
    *   Calculate if a ray is scattered and the amount of absorbed energy depending on the material implementation.
    *   
    *   @param ray The incoming ray which may be either scattered or absorbed by the material
    *   @param hit_record  Data container to keep track of the ray hit data
    *   @param attenuation How much energy the material absorbs
    *   @param scattered_ray   The resulting ray if the material scattered the incoming ray
    *   @return True if the incoming ray was scattered
    */
    virtual bool Scatter(const Ray& ray, const HitRecord& hit_record, Color& attenuation, Ray& scattered_ray) const = 0;
};
