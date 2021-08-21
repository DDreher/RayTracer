#include "Ray.h"
#include "RayTracer.h"
#include "Vector.h"

Color CalculateRayColor(const Ray& r)
{
    Vec3 direction = MakeUnitVec(r.GetDirection());

    // linearly blend white and blue depending on the height of the y coordinate after scaling the ray direction to unit length
    // -> -1.0f <= y <= 1.0f
    float t = 0.5f * (direction.y_ + 1.0f); // scale to [0.0f, 1.0f] range

    // then do a simple lerp between the two colors
    static const Color OtherColor = Color(0.5f, 0.7f, 1.0f);
    return (1.0f - t) * Color::WHITE + t * OtherColor;
}

int main()
{
    // Image definitions
    const float aspect_ratio = 16.0f / 9.0f;
    const uint32 image_width = 400;
    const uint32 image_height = static_cast<uint32>(image_width / aspect_ratio);

    // Set up a virtual viewport
    float viewport_height = 2.0f;
    float viewport_width = aspect_ratio * viewport_height;
    float focal_length = 1.0f; // distance between the projection plane and the projection point (NOT focus distance!)
    Vec3 horizontal_axis = Vec3(viewport_width, 0.0f, 0.0f);
    Vec3 vertical_axis = Vec3(0.0f, viewport_height, 0.0f);

    // Camera
    Point3 camera_pos;
    Vec3 lower_left_corner = camera_pos - horizontal_axis * 0.5f - vertical_axis * 0.5f - Vec3(0.0f, 0.0f, focal_length);

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (uint32 i = 0; i < image_width; ++i)
        {
            // Coordinates in viewport space
            float u = static_cast<float>(i) / (image_width - 1.0f);
            float v = static_cast<float>(j) / (image_height - 1.0f);

            const Vec3 ray_direction = lower_left_corner + u * horizontal_axis + v * vertical_axis - camera_pos;
            Ray ray(camera_pos, ray_direction);

            Color pixel_color = CalculateRayColor(ray);
            WritePixel(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone.\n";
}
