#include "RayTracer.h"
#include "Vector.h"

Color RayTracer::CalcRayColor(const Ray& r, const IHittable& scene_objects)
{
    const float t_min = 0.0f;
    const float t_max = INF;
    HitRecord hit_record;

    // Check for object intersections
    if (scene_objects.Hit(r, t_min, t_max, hit_record))
    {
        return 0.5f * (hit_record.surface_normal_ + Color::WHITE);
    }

    // Else calculate background color

    // linearly blend white and blue depending on the height of the y coordinate after scaling the ray direction to unit length
    // -> -1.0f <= y <= 1.0f
    Vec3 direction = MakeUnitVec(r.GetDirection());
    float t = 0.5f * (direction.y_ + 1.0f); // scale to [0.0f, 1.0f] range

    // then do a simple lerp between the two colors
    static const Color other_color = Color(0.5f, 0.7f, 1.0f);
    return (1.0f - t) * Color::WHITE + t * other_color;
}
