#pragma once
#include "Hittable.h"

class Triangle : public IHittable
{
public:
    Triangle() {}
    Triangle(Point3 v0, Point3 v1, Point3 v2, Vec3 normal, const SharedPtr<IMaterial>& material);

    // Begin IHittable
    virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& hit_record) const override;
    // End IHittable

private:
    Vec3 v0_;
    Vec3 v1_;
    Vec3 v2_;
    Vec3 v0v1_;
    Vec3 v0v2_;
    Vec3 surface_normal_;
    SharedPtr<IMaterial> material_;
};