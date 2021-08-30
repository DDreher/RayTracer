#pragma once
#include "Material.h"

/**
*    Abstraction of dieletric materials, i.e. water, glass, etc.
*/
class Dielectric : public IMaterial
{
public:
    Dielectric(float refraction_index)
        : refraction_index_(refraction_index)
    {
    };

    // Begin IMaterial
    virtual bool Scatter(const Ray& ray, const HitRecord& hit_record, Color& attenuation, Ray& scattered_ray) const override;
    // End IMaterial

public:
    float refraction_index_ = 1.0f;

private:
    /**
    *    Calculate reflectance according to Christophe Schlick's approximation.
    *    
    *    @param cosine  Angle between the ray and the surface normal
    *    @param refraction_index    Refraction ratio between the two materials
    *    @return The reflectance    The reflectivity of the material
    */
    static float CalculateReflectance(float cosine, float refraction_index);
};
