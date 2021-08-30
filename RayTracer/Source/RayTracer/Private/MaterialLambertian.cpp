#include "MaterialLambertian.h"

bool Lambertian::Scatter(const Ray& ray, const HitRecord& hit_record, Color& attenuation, Ray& scattered_ray) const
{
    // Lambertian reflection - Reflect along the direction of a normalized vector pointing to a random point on the surface of a unit sphere
    Vec3 scatter_direction = hit_record.surface_normal_ + Vec3::GetRandomUnitVector();

    // Take care of degenerate scatter direction.
    // This may happen if the hit surface normal and the random unit vector (nearly) negate each other.
    if(scatter_direction.IsZero())
    {
        scatter_direction = hit_record.surface_normal_;
    }

    scattered_ray = Ray(hit_record.position_, scatter_direction);
    attenuation = albedo_;
    return true;
}
