#pragma once
#include "Ray.h"
#include "Hittable.h"

struct RayTracer
{
    /**
    *    Shoots a ray into the scene and calculates its color.
    *    Rays may be reflected and in turn call this function recursively to figure out the final color.
    *    
    *    @param r   Ray we use to check intersections
    *    @param scene_objects   Objects in the scene we check for intersections
    *    @param num_bounces Maximum number of times the ray can bounce off objects in the scene
    *    @return The final color of the ray after it bounced off the objects in the scene
    */
    static Color CalcRayColor(const Ray& r, const IHittable& scene_objects, uint32 num_bounces);
};
