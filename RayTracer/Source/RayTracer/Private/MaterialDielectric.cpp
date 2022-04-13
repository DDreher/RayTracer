#include "MaterialDielectric.h"

bool Dielectric::Scatter(const Ray& ray, const HitRecord& hit_record, Color& attenuation, Ray& scattered_ray) const
{
    attenuation = Color::WHITE; // Glass absorbs nothing
    Vec3 unit_direction = Normalize(ray.direction_);

    // When ray is in the material with higher refractive index, there is no real solution to Snell's law (which is used to calculate the refracted ray)
    // -> There is no refraction possible, so the ray has to be reflected.
    // "Total Internal Reflection", see https://raytracing.github.io/books/RayTracingInOneWeekend.html#dielectrics/totalinternalreflection
    float cos_theta = fminf(Dot(-unit_direction, hit_record.surface_normal_), 1.0f);
    float sin_theta = sqrtf(1.0f - cos_theta * cos_theta);
    float refraction_ratio = hit_record.is_surface_outside_ ? (1.0f / refraction_index_) : refraction_index_;

    Vec3 scattered_ray_direction;
    bool can_refract = refraction_ratio * sin_theta <= 1.0f;

    // Reflectivity varies with angle. If you look at a window at a steep angle it reflects a lot of light.
    // We appromixate this behavior with the "Schlick Approximation".
    bool should_reflect_due_to_steep_angle = CalculateReflectance(cos_theta, refraction_ratio) > Rand();
    if(can_refract == false || should_reflect_due_to_steep_angle)
    {
        // Can't refract -> must reflect
        scattered_ray_direction = Vec3::Reflect(unit_direction, hit_record.surface_normal_);
    }
    else
    {
        scattered_ray_direction = Vec3::Refract(unit_direction, hit_record.surface_normal_, refraction_ratio);
    }

    scattered_ray = Ray(hit_record.position_, scattered_ray_direction);
    return true;
}

float Dielectric::CalculateReflectance(float cosine, float refraction_index)
{
    float r0 = (1.0f - refraction_index) / (1.0f+refraction_index);
    r0 = r0 * r0;
    return r0 + (1.0f - r0) * powf(1.0f - cosine, 5.0f);
}
