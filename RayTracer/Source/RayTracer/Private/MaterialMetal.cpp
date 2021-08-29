#include "MaterialMetal.h"

bool Metal::Scatter(const Ray& ray, const HitRecord& hit_record, Color& attenuation, Ray& scattered_ray) const
{
    // Reflect incoming ray along the surface normal
    Vec3 scatter_direction = Vec3::Reflect(MakeUnitVec(ray.direction_), hit_record.surface_normal_);
    scattered_ray = Ray(hit_record.position_, scatter_direction);
    attenuation = albedo_;

    // Dot product == 1 -> vectors are in same direction
    // Dot product == 0 -> vectors are orthogonal
    // Dot procut == -1 -> vectors are in opposite directions
    // ==> If the dot product moves towards -1, the ray would be absorbed since it moves into the surfaces
    return Dot(scatter_direction, hit_record.surface_normal_) > 0;
}
