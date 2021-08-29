#pragma once
#include "Hittable.h"

class Sphere : public IHittable
{
public:
    Sphere() {}
    Sphere(const Vec3& position, float radius, const SharedPtr<IMaterial>& material)
        : position_(position), radius_(radius), material_(material)
    {}

    // Begin IHittable
    virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& hit_record) const override;
    // End IHittable

    static Vec3 RandomUnit(float min, float max);

private:
    Vec3 position_;
    float radius_ = 0.0f;
    SharedPtr<IMaterial> material_;
};
