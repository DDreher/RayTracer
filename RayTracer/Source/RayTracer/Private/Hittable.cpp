#include "Hittable.h"

HittableList::HittableList(const SharedPtr<IHittable>& object)
{
    Add(object);
}

bool HittableList::Hit(const Ray& r, float t_min, float t_max, HitRecord& hit_record) const
{
    HitRecord tmp_hit_record;
    bool has_hit_anything = false;
    float closest_t = t_max;

    // Check all objects in the scene for intersections
    for (const SharedPtr<IHittable>& object : objects_)
    {
        if (object->Hit(r, t_min, closest_t, tmp_hit_record))
        {
            has_hit_anything = true;

            // We only care about the closest object we hit
            closest_t = tmp_hit_record.t_;
            hit_record = tmp_hit_record;
        }
    }

    return has_hit_anything;
}

void HittableList::Clear()
{
    objects_.clear();
}

void HittableList::Add(const SharedPtr<IHittable>& object)
{
    objects_.push_back(object);
}
