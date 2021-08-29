#include "Camera.h"
#include "Hittable.h"
#include "Image.h"
#include "MaterialLambertian.h"
#include "MaterialMetal.h"
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

    const float focal_length = 1.0f;
    Camera cam(aspect_ratio, focal_length);

    // World
    HittableList scene_objects;
    
    SharedPtr<IMaterial> material_diffuse = MakeShared<Lambertian>(Color(0.8f, 0.2f, 0.2f));
    SharedPtr<IMaterial> material_ground = MakeShared<Lambertian>(Color(0.8f, 0.8f, 0.0f));
    SharedPtr<IMaterial> material_metal = MakeShared<Metal>(Color(0.39f, 0.58f, 0.92f));
    
    scene_objects.Add(MakeShared<Sphere>(Vec3(0.0f, -100.5f, -1.0f), 100.0f, material_ground));
    scene_objects.Add(MakeShared<Sphere>(Vec3(1.5f, 0.0f, -2.0f), 0.5f, material_diffuse));
    scene_objects.Add(MakeShared<Sphere>(Vec3(-.5f, 0.0f, -1.0f), 0.5f, material_metal));

    // Ray tracing - Shoot a ray into the scene for each pixel
    static const uint32 samples_per_pixel = 100;
    static const uint32 max_bounces = 50;
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
                pixel_color += RayTracer::CalcRayColor(ray, scene_objects, max_bounces);
            }

            // Calculate final color values by averaging all the samples
            pixel_color /= samples_per_pixel;

            // Gamma correction 
            // Image viewers assume images to be gamma corrected, i.e. the color values are transformed in some way
            // before being stored as bytes. In this case we use Gamma 2, i.e. we raise the color to the power 1/gamma with gamma = 2,
            // which is just the square root.
            pixel_color.x_ = sqrtf(pixel_color.x_);
            pixel_color.y_ = sqrtf(pixel_color.y_);
            pixel_color.z_ = sqrtf(pixel_color.z_);

            // Convert to pixel coordinates and write color to the output image
            size_t pixel_x = i;
            size_t pixel_y = image.GetHeight() - 1 - j;
            image.SetPixel(pixel_x, pixel_y, pixel_color);
        }

        if(j==0)
        {
            // Break out before overflow
            break;
        }
    }

    String output_name = "output.png";
    image.Save(output_name.c_str());
    LOG("Done! Saved output image as '%s'", output_name);
}
