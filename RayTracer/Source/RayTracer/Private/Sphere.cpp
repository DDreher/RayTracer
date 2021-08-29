#include "Sphere.h"

bool Sphere::Hit(const Ray& r, float t_min, float t_max, HitRecord& hit_record) const
{
    // Sphere equation: x^2 + y^2 + z^2 = R^2
    // Or (x - C_x)^2 + (y - C_y)^2 + (z - C_z)^2 = r^2
    // <=> (P(t)-C) dot (P(t)-C) = r^2
    // If we insert the ray equation we get:
    // t^2b^2+2tb dot (A-C)+(A-C) dot (A-C)-r^2=0
    // Which we can then solve for t to get the intersection points.
    // Depending on the discriminant we then know if we hit the sphere:
    // negative -> no real solution -> 0 intersections
    // zero -> exactly one real solution -> 1 intersection
    // positive -> two real solutions -> 2 intersections
    // School maths at its finest 8)

    // Solve the resulting quadratic equation with abc-formula
    Vec3 center_to_origin = r.GetOrigin() - position_;
    const float a = Dot(r.GetDirection(), r.GetDirection());
    const float half_b = Dot(center_to_origin, r.GetDirection());   // If we use half_b instead of b we can get rid of the factor 2.
    const float c = center_to_origin.LengthSquared() - radius_ * radius_;
    const float discriminant = half_b * half_b - a * c;

    if (discriminant < 0.0f)
    {
        // No real solution -> Ray didn't hit the sphere
        return false;
    }

    // There are two possibilities: 1 hit point or 2 hit points.
    // We only want the nearest hit point in the given accepted range.
    const float root_discriminant = sqrtf(discriminant);
    const float a_inv = 1.0f / a;

    float t = (-half_b - root_discriminant) * a_inv;
    if(t < t_min || t > t_max)
    {
        // Out of accepted bounds -> Check again for other possible hit point
        t = (-half_b + root_discriminant) * a_inv;
        if (t < t_min || t > t_max)
        {
            // No accepted solution
            return false;
        }
    }

    hit_record.t_ = t;
    hit_record.position_ = r.At(t);
    Vec3 outside_normal = (hit_record.position_ - position_) / radius_;  // Divide by the sphere radius so we get a unit vec
    hit_record.SetSurfaceNormal(r, outside_normal);
    hit_record.material_ = material_;
    return true;
}
