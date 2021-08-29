#include "Camera.h"
#include "Hittable.h"
#include "Image.h"
#include "MaterialDielectric.h"
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
    const size_t image_width = 512;
    const size_t image_height = static_cast<size_t>(image_width / aspect_ratio);
    Image image(image_width, image_height);

    static const Vec3 WORLD_UP = Vec3(0.0f, 1.0f, 0.0f);
    static const Vec3 WORLD_FORWARD = Vec3(0.0f, 0.0f, -1.0f);
    static const Vec3 WORLD_ORIGIN = Vec3(0.0f, 0.0f, 0.0f);

    Vec3 camera_pos = WORLD_ORIGIN + Vec3(-2.0f, 0.7f, .75f);
    Vec3 camera_look_at = Vec3(0.0f, 0.0f, -1.0f);

    CameraAttributes cam_attributes;
    cam_attributes.vertical_fov_degrees_ = 45.0f;
    cam_attributes.focus_distance_ = (camera_pos - Vec3(-1.0f, 0.0f, -1.0f)).Length();
    cam_attributes.aperture_ = 0.025f;
    Camera cam(camera_pos, camera_look_at, WORLD_UP, cam_attributes);

    // World
    HittableList scene_objects;
    
    SharedPtr<IMaterial> material_diffuse = MakeShared<Lambertian>(Color(0.9f, 0.1f, 0.1f));
    SharedPtr<IMaterial> material_ground = MakeShared<Lambertian>(Color(107.0f / 255.0f, 142.0f / 255.0f, 35.0f / 255.0f));
    SharedPtr<IMaterial> material_metal_rougher = MakeShared<Metal>(Color(0.39f, 0.58f, 0.92f), 0.8f);
    SharedPtr<IMaterial> material_metal_smooth = MakeShared<Metal>(Color(240.0f / 255.0f, 225.0f / 255.0f, 48.0f / 255.0f), 0.01f);
    SharedPtr<IMaterial> material_glass = MakeShared<Dielectric>(1.5f);
    
    scene_objects.Add(MakeShared<Sphere>(Point3(0.0f, -100.5f, -1.0f), 100.0f, material_ground));
    scene_objects.Add(MakeShared<Sphere>(Point3(-1.0f, 0.0f, -1.0f), 0.5f, material_glass));
    scene_objects.Add(MakeShared<Sphere>(Point3(-1.0f, 0.0f, -1.0f), -0.4f, material_glass));   // We can fake hollow glass spheres by using a negative radius
                                                                                                // -> surface normals point inwards
    scene_objects.Add(MakeShared<Sphere>(Point3(0.0f, 0.0f, -1.0f), 0.5f, material_diffuse));
    scene_objects.Add(MakeShared<Sphere>(Point3(1.0f, 0.0f, -1.0f), 0.5f, material_metal_rougher));
    scene_objects.Add(MakeShared<Sphere>(Point3(2.0f, 0.0f, -1.0f), 0.5f, material_metal_smooth));

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
