#include "Ray.h"
#include "RayTracer.h"
#include "Vector.h"
#include "Image.h"

float CalcRaySphereIntersection(const Ray& ray, const Point3& sphere_center, float sphere_radius)
{
    // Sphere equation: x^2 + y^2 + z^2 = R^2
    // Or (x - C_x)^2 + (y - C_y)^2 + (z - C_z)^2 = r^2
    // <=> (P(t)-C) dot (P(t)-C) = r^2
    // If we insert the ray equation we get:
    // t^2b^2+2tb⋅(A−C)+(A−C)⋅(A−C)−r^2=0
    // Which we can then solve for t to get the intersection points.
    // Depending on the discriminant we then know if we hit the sphere:
    // negative -> no real solution -> 0 intersections
    // zero -> exactly one real solution -> 1 intersection
    // positive -> two real solutions -> 2 intersections
    // School maths at its finest 8)
     
    Vec3 center_to_origin = ray.GetOrigin() - sphere_center;
    float a = Dot(ray.GetDirection(), ray.GetDirection());
    float b = 2.0f * Dot(center_to_origin, ray.GetDirection());
    float c = Dot(center_to_origin, center_to_origin) - sphere_radius * sphere_radius;
    float discriminant = b * b - 4.0f * a * c;
    
    if(discriminant < 0.0f)
    {
        return -1.0f;
    }
    else
    {
        return (-b - sqrtf(discriminant) * 0.5f * a);
    }
}

Color CalcRayColor(const Ray& r)
{
    Vec3 direction = MakeUnitVec(r.GetDirection());

    Vec3 sphere_center = Point3(0.0f, 0.0f, -1.0f);
    float sphere_radius = 0.5f;

    float t = CalcRaySphereIntersection(r, sphere_center, sphere_radius);

    if(t > 0.0f) // We hit the sphere
    {
        Vec3 normal = MakeUnitVec(r.At(t) - Vec3(sphere_center));
        return 0.5f * Color(normal.x_ + 1.0f, normal.y_ + 1.0f, normal.z_ + 1.0f);  // Normals are [-1,1], so we have to scale to [0,1] for color!
    }

    // linearly blend white and blue depending on the height of the y coordinate after scaling the ray direction to unit length
    // -> -1.0f <= y <= 1.0f
    t = 0.5f * (direction.y_ + 1.0f); // scale to [0.0f, 1.0f] range

    // then do a simple lerp between the two colors
    static const Color other_color = Color(0.5f, 0.7f, 1.0f);
    return (1.0f - t) * Color::WHITE + t * other_color;
}

int main()
{
    // Image definitions
    const float aspect_ratio = 16.0f / 9.0f;
    const size_t image_width = 400;
    const size_t image_height = static_cast<size_t>(image_width / aspect_ratio);
    Image image(image_width, image_height);

    // Set up a virtual viewport
    float viewport_height = 2.0f;
    float viewport_width = aspect_ratio * viewport_height;
    float focal_length = 1.0f; // distance between the projection plane and the projection point (NOT focus distance!)
    Vec3 horizontal_axis = Vec3(viewport_width, 0.0f, 0.0f);
    Vec3 vertical_axis = Vec3(0.0f, viewport_height, 0.0f);

    // Camera
    Point3 camera_pos;
    Vec3 lower_left_corner = camera_pos - horizontal_axis * 0.5f - vertical_axis * 0.5f - Vec3(0.0f, 0.0f, focal_length);

    // Ray tracing - Shoot a ray into the scene for each pixel
    for (size_t j = image.GetHeight() - 1; ; --j)
    {
        std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (size_t i = 0; i < image_width; ++i)
        {
            // Coordinates in viewport space
            float u = static_cast<float>(i) / (image_width - 1.0f);
            float v = static_cast<float>(j) / (image_height - 1.0f);

            const Vec3 ray_direction = lower_left_corner + u * horizontal_axis + v * vertical_axis - camera_pos;
            Ray ray(camera_pos, ray_direction);

            Color pixel_color = CalcRayColor(ray);

            // Convert to pixel coordinates
            size_t pixel_y = image.GetHeight() - 1 - j;
            size_t pixel_x = i;

            image.SetPixel(pixel_x, pixel_y, pixel_color);
        }

        if(j==0)
        {
            // Manually break out before overflow
            break;
        }
    }

    image.Save("output.png");

    std::cout << "\nDone.\n";
}
