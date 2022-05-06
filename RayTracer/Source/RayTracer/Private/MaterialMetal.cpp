#include "MaterialMetal.h"

bool Metal::Scatter(const Ray& ray, const HitRecord& hit_record, Color& attenuation, Ray& scattered_ray) const
{
    // Reflect incoming ray along the surface normal
    Vec3 reflected_ray_dir = glm::reflect(glm::normalize(ray.direction_), hit_record.surface_normal_);
    Vec3 scatter_direction = reflected_ray_dir + fuzziness_ * glm::sphericalRand(1.0f);
    scattered_ray = Ray(hit_record.position_, scatter_direction);
    attenuation = albedo_;

    // Dot product == 1 -> vectors are in same direction
    // Dot product == 0 -> vectors are orthogonal
    // Dot procut == -1 -> vectors are in opposite directions
    // ==> If the dot product moves towards -1, the ray would be absorbed since it moves into the surfaces
    return glm::dot(scatter_direction, hit_record.surface_normal_) > 0;
}
