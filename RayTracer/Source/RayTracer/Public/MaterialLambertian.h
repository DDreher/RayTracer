#pragma once
#include "Material.h"

/**
*    Abstraction of lambertian/diffuse materials.
*    This implementation always scatters and attenuates the color by its reflectance.
*    Alternative: Scatter with no attenuation but absorb fraction 1.0f - reflectance of the rays (or a mixture of both options).
*/
class Lambertian : public IMaterial
{
public:
    Lambertian(const Color& color)
        : albedo_(color)
    {};

    // Begin IMaterial
    virtual bool Scatter(const Ray& ray, const HitRecord& hit_record, Color& attenuation, Ray& scattered_ray) const override;
    // End IMaterial

public:
    Color albedo_;  // Measure of the diffuse reflection
};
