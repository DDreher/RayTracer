#pragma once
#include "Hittable.h"

class Sphere : public IHittable
{
public:
    Sphere() {}
    Sphere(const Vec3& position, float radius)
        : position_(position), radius_(radius)
    {}

    // Begin IHittable
    virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& hit_record) const override;
    // End IHittable

private:
    Vec3 position_;
    float radius_ = 0.0f;
};
