#pragma once
#include "Hittable.h"
#include "Vertex.h"

class Triangle : public IHittable
{
public:
    Triangle() {}
    Triangle(Vertex v0, Vertex v1, Vertex v2, const SharedPtr<IMaterial>& material);

    // Begin IHittable
    virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& hit_record) const override;
    // End IHittable

private:
    Vertex v0_;
    Vertex v1_;
    Vertex v2_;
    Vec3 v0v1_;
    Vec3 v0v2_;
    SharedPtr<IMaterial> material_;
};