#include "RayTracer.h"
#include "Vector.h"
#include "Sphere.h"

Color RayTracer::CalcRayColor(const Ray& r, const IHittable& scene_objects, uint32 num_bounces)
{
    if(num_bounces <= 0)
    {
        // Reached the maximum number of bounces for the ray
        // -> No further contribution to the color
        return Color::BLACK;
    }

    // Check for object intersections
    static const float t_min = 0.001f;  // This can't be exactly zero, otherwise reflected rays would start directly in the surface and bounce right off again!
    static const float t_max = INF;
    HitRecord hit_record;
    if (scene_objects.Hit(r, t_min, t_max, hit_record))
    {
        // Calculate color for a diffuse (matte) material.
        // Diffuse materials take on the color of their surroundings.
        // Rays are reflected in random directions or absorbed.
        
        // Lambertian reflection
        // Reflect along the direction of a normalized vector pointing to a random point on the surface of a unit sphere tangent to the hit point of the surface.
        // Alternative: Pick a random point on a hemisphere in which the surface normal is in.
        const Point3 reflection_target = hit_record.position_ + hit_record.surface_normal_ + Vec3::GetRandomUnitVector();
        const Ray reflected_ray = Ray(hit_record.position_, reflection_target - hit_record.position_);

        // Then cast the child ray into the scene
        static const float reflectance_factor = 0.5f;   // absorb half the energy on each bounce
        return reflectance_factor * CalcRayColor(reflected_ray, scene_objects, num_bounces-1);
    }

    // If there's no intersection simply calculate background color

    // linearly blend white and blue depending on the height of the y coordinate after scaling the ray direction to unit length
    // -> -1.0f <= y <= 1.0f
    Vec3 direction = MakeUnitVec(r.GetDirection());
    float t = 0.5f * (direction.y_ + 1.0f); // scale to [0.0f, 1.0f] range

    // then do a simple lerp between the two colors
    static const Color other_color = Color(0.5f, 0.7f, 1.0f);
    return (1.0f - t) * Color::WHITE + t * other_color;
}
