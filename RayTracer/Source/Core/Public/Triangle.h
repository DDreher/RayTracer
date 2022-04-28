#pragma once
#include "Hittable.h"
#include "Vertex.h"

class Triangle : public IHittable
{
public:
    Triangle() {}
    Triangle(Vertex v0, Vertex v1, Vertex v2);

    // Begin IHittable
    virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& hit_record) const override;
    // End IHittable

    inline Vec3 GetNormal(float u, float v) const
    {
        Vec3 normal = Vec3(0.0f, 0.0f, 0.0f);

        if (v0_.normal_ && v1_.normal_ && v2_.normal_)
        {
            const float w = 1.0f - u - v;
            return glm::normalize(w * v0_.normal_.value() + u * v1_.normal_.value() + v * v2_.normal_.value());
        }

        return normal;
    }

    inline Vec3 GetTexCoords(float u, float v) const
    {
        Vec3 tex_coords_ = Vec3(0.0f, 0.0f, 0.0f);

        if (v0_.tex_coords_ && v1_.tex_coords_ && v2_.tex_coords_)
        {
            const float w = 1.0f - u - v;
            return w * v0_.tex_coords_.value() + u * v1_.tex_coords_.value() + v * v2_.tex_coords_.value();
        }

        return tex_coords_;
    }

private:
    Vertex v0_;
    Vertex v1_;
    Vertex v2_;
    Vec3 v0v1_;
    Vec3 v0v2_;
};