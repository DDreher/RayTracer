#pragma once
#include "Material.h"

/**
*    Abstraction of a metal material.
*    This implementation just reflects rays.
*/
class Metal : public IMaterial
{
public:
    Metal(const Color& color, float fuzziness)
        : albedo_(color)
        , fuzziness_(fuzziness < 1.0f ? fuzziness : 1.0f)
    {};

    // Begin IMaterial
    virtual bool Scatter(const Ray& ray, const HitRecord& hit_record, Color& attenuation, Ray& scattered_ray) const override;
    // End IMaterial

public:
    Color albedo_;  // Measure of the diffuse reflection
    float fuzziness_ = 1.0f;    // The bigger the sphere, the fuzzier the reflections are.
};
