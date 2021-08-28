#include "Hittable.h"
#include "Image.h"
#include "Ray.h"
#include "RayTracer.h"
#include "Sphere.h"
#include "Vector.h"

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

    // World
    HittableList scene_objects;
    scene_objects.Add(MakeShared<Sphere>(Vec3(0.0f, 0.0f, -1.0f), 0.5f));
    scene_objects.Add(MakeShared<Sphere>(Vec3(0.0f, -100.5f, -1.0f), 100.0f));

    // Ray tracing - Shoot a ray into the scene for each pixel
    for (size_t j = image.GetHeight() - 1; ; --j)
    {
        LOG("Scanlines remaining: %i", j);
        for (size_t i = 0; i < image_width; ++i)
        {
            // Coordinates in viewport space
            float u = static_cast<float>(i) / (image_width - 1.0f);
            float v = static_cast<float>(j) / (image_height - 1.0f);

            // Cast ray into the scene
            const Vec3 ray_direction = lower_left_corner + u * horizontal_axis + v * vertical_axis - camera_pos;
            Ray ray(camera_pos, ray_direction);
            Color pixel_color = RayTracer::CalcRayColor(ray, scene_objects);

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

    String output_name = "output.png";
    image.Save(output_name.c_str());
    LOG("Done! Saved output image as '%s'", output_name);
}
