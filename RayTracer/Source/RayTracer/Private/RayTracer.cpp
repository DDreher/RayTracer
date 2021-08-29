#include "Hittable.h"
#include "Material.h"
#include "RayTracer.h"
#include "Vector.h"

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
        Ray scattered_ray;
        Color attenuation;  // How much energy to absorb

        // Check for color contribution depending on the object's material
        if(hit_record.material_->Scatter(r, hit_record, attenuation, scattered_ray))
        {
            // Ray was scattered -> Cast scattered child ray into the scene
            // And accumulate color contributions from other bounces
            return attenuation * CalcRayColor(scattered_ray, scene_objects, num_bounces - 1);
        }
        else
        {   
            // Ray was fully absorbed -> Black
            return Color::BLACK;
        }
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
