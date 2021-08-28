#include "Hittable.h"
#include "Image.h"
#include "Ray.h"
#include "RayTracer.h"
#include "Sphere.h"
#include "Vector.h"
#include "Camera.h"

int main()
{
    // Image definitions
    const float aspect_ratio = 16.0f / 9.0f;
    const size_t image_width = 400;
    const size_t image_height = static_cast<size_t>(image_width / aspect_ratio);
    Image image(image_width, image_height);

    const float focal_length = 1.0f;
    Camera cam(aspect_ratio, focal_length);

    // World
    HittableList scene_objects;
    scene_objects.Add(MakeShared<Sphere>(Vec3(0.0f, 0.0f, -1.0f), 0.5f));
    scene_objects.Add(MakeShared<Sphere>(Vec3(0.0f, -100.5f, -1.0f), 100.0f));

    // Ray tracing - Shoot a ray into the scene for each pixel
    const uint32 samples_per_pixel = 100;
    for (size_t j = image.GetHeight() - 1; ; --j)
    {
        LOG("Scanlines remaining: %i", j);
        for (size_t i = 0; i < image_width; ++i)
        {
            Color pixel_color;

            // Calculate multiple samples per pixel for antialiasing
            for(uint32_t sample_idx=0; sample_idx<samples_per_pixel; ++sample_idx)
            {
                // Coordinates in viewport space
                float u = static_cast<float>(i+Rand()) / (image_width - 1.0f);
                float v = static_cast<float>(j+Rand()) / (image_height - 1.0f);

                // Cast ray into the scene and accumulate the sample values
                Ray ray = cam.GetRay(u, v);
                pixel_color += RayTracer::CalcRayColor(ray, scene_objects);
            }

            // Calculate final color values by averaging all the samples
            pixel_color /= samples_per_pixel;

            // Convert to pixel coordinates and write color to the output image
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
