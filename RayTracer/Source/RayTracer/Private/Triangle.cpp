#include "Triangle.h"

Triangle::Triangle(Vertex v0, Vertex v1, Vertex v2, const SharedPtr<IMaterial>& material)
    : v0_(v0), v1_(v1), v2_(v2), material_(material)
{
    v0v1_ = v1_.position_ - v0_.position_;
    v0v2_ = v2_.position_ - v0_.position_;
}

bool Triangle::Hit(const Ray& r, float t_min, float t_max, HitRecord& hit_record) const
{
    // Great explanation for...
    // ... plane equation: https://www.youtube.com/watch?v=TnHQ9vJR2V4
    // ... ray-triangle-intersection: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/why-are-triangles-useful
    
    // In this case we use the Möller-Trumbore algorithm:
    // Paper: Fast, minimum storage ray-triangle intersection.
    // Tomas Möller and Ben Trumbore. 
    // Journal of Graphics Tools, 2(1):21--28, 1997. 
    // http://www.graphics.cornell.edu/pubs/1997/MT97.pdf
    // 
    // Resources:
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection
    // https://www.youtube.com/watch?v=fK1RPmF_zjQ


    Vec3 p_vec = Cross(r.direction_, v0v2_);
    float determinant = Dot(v0v1_, p_vec);
    if(IsNearlyZero(determinant))
    {
        // if the determinant is negative the triangle is backfacing
        // if the determinant is close to 0, the ray misses the triangle
        return false;
    }

    float inv_determinant = 1.0f / determinant;

    Vec3 t_axis = r.origin_ - v0_.position_;
    float u = Dot(t_axis, p_vec) * inv_determinant;
    if (u < 0.0f || u > 1.0f)
    {
        // if u out of [0.0f, 1.0f] bounds, then we know that p is not inside the triangle
        return false;
    }

    Vec3 q_axis = Cross(t_axis, v0v1_);
    float v = Dot(r.direction_, q_axis) * inv_determinant;
    if (v < 0.0f || u + v > 1.0f)
    {
        // if v out of [0.0f, 1.0f] bounds, then we know that p is not inside the triangle
        return false;
    }

    float t = Dot(v0v2_, q_axis) * inv_determinant;
    if (t < t_min || t > t_max)
    {
        // We only care about the closest surface we hit
        return false;
    }

    hit_record.u_ = u;
    hit_record.v_ = v;
    hit_record.t_ = t;
    hit_record.position_ = r.At(t);

    const float w = 1.0f - u - v;
    Vec3 normal = Normalize(w * v0_.normal_ + u * v1_.normal_ + v * v2_.normal_);
    hit_record.SetSurfaceNormal(r, normal);
    hit_record.material_ = material_;

    return true;
}
