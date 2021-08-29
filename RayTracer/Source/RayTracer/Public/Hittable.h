#pragma once
#include "Ray.h"
#include "Vector.h"

/**
*    Container for data we're interested in whenever a ray hits an entity in the scene
*/
struct HitRecord
{
    Point3 position_;
    Vec3 surface_normal_;
    SharedPtr<class IMaterial> material_;
    float t_ = 0.0f;
    bool is_surface_outside_ = false;

    /**
    *    Determine if the ray hit the inside or the outside of an object at geometry time.
    *    Sets is_surface_outside and the surface normal depending on the ray and the normal pointing outside.
    *    If the normal points towards the ray, then is_front_face is true (the ray is outside the object).
    *    If the normal points away from the ray, then is_front_face is false (the ray is inside the object).
    *    
    *    @param r   The ray for which we determine the direction of the face it hit
    *    @param outside_normal The normal at the hit point which points outside of the object
    */
    inline void SetSurfaceNormal(const Ray& r,  const Vec3& outside_normal)
    {
        // We can check if the normal points towards/against the ray by calculating a dot product.
        is_surface_outside_ = Dot(r.GetDirection(), outside_normal) < 0.0f;
        surface_normal_ = is_surface_outside_ ? outside_normal : -outside_normal;
    }
};

/**
*    Interface for anything in a scene that our rays can hit (objects or volumes)
*/
class IHittable
{
public:
    virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& hit_record) const = 0;
};

class HittableList : public IHittable
{
public:
    HittableList() = default;
    HittableList(const SharedPtr<IHittable>& object);

    // Begin IHittable
    virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& hit_record) const override;
    // End IHittable

    void Clear();

    void Add(const SharedPtr<IHittable>& object);

private:
    Array<SharedPtr<IHittable>> objects_;
};
