#pragma once
#include "Material.h"

/**
*    Abstraction of a metal material.
*    This implementation just reflects rays.
*/
class Metal : public IMaterial
{
public:
    Metal(const Color& color)
        : albedo_(color)
    {};

    // Begin IMaterial
    virtual bool Scatter(const Ray& ray, const HitRecord& hit_record, Color& attenuation, Ray& scattered_ray) const override;
    // End IMaterial

public:
    Color albedo_;  // Measure of the diffuse reflection
};
