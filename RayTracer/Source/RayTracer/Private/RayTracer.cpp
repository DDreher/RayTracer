#include "Image.h"
#include "Material.h"
#include "RayTracer.h"
#include "Vector.h"

Color RayTracer::CalcRayColor(const Ray& r, const IHittable& scene_objects, uint32 num_bounces)
{
    if(num_bounces <= 0)
    {
        // Reached the maximum number of bounces for the ray
        // -> No further contribution to the color
        return Color::BLACK;
    }

    // Check for object intersections
    static const float t_min = 0.001f;  // This can't be exactly zero, otherwise reflected rays would start directly in the surface and bounce right off again!
    static const float t_max = FLOAT_INF;
    HitRecord hit_record;
    if (scene_objects.Hit(r, t_min, t_max, hit_record))
    {
        Ray scattered_ray;
        Color attenuation;  // How much energy to absorb

        // Check for color contribution depending on the object's material
        if(hit_record.material_->Scatter(r, hit_record, attenuation, scattered_ray))
        {
            // Ray was scattered -> Cast scattered child ray into the scene
            // And accumulate color contributions from other bounces
            return attenuation * CalcRayColor(scattered_ray, scene_objects, num_bounces - 1);
        }
        else
        {   
            // Ray was fully absorbed -> Black
            return Color::BLACK;
        }
    }

    // If there's no intersection simply calculate background color

    // linearly blend white and blue depending on the height of the y coordinate after scaling the ray direction to unit length
    // -> -1.0f <= y <= 1.0f
    Vec3 direction = Normalize(r.direction_);
    float t = 0.5f * (direction.y_ + 1.0f); // scale to [0.0f, 1.0f] range

    // then do a simple lerp between the two colors
    static const Color other_color = Color(0.5f, 0.7f, 1.0f);
    return (1.0f - t) * Color::WHITE + t * other_color;
}

void RayTracer::Trace(const Scene& scene)
{
    size_t image_width = settings_.output_settings_.image_width_;
    size_t image_height = settings_.output_settings_.image_height_;
    Image image(image_width, image_height);

    // Shoot a ray into the scene for each pixel
    for (size_t j = image.GetHeight() - 1; ; --j)
    {
        LOG("Scanlines remaining: {}", j);
        for (size_t i = 0; i < image_width; ++i)
        {
            Color pixel_color;

            // Calculate multiple samples per pixel for antialiasing
            for (uint32_t sample_idx = 0; sample_idx < settings_.quality_settings_.samples_per_pixel_; ++sample_idx)
            {
                // Coordinates in viewport space
                float u = static_cast<float>(i + Rand()) / (image_width - 1.0f);
                float v = static_cast<float>(j + Rand()) / (image_height - 1.0f);

                // Cast ray into the scene and accumulate the sample values
                Ray ray = scene.camera_.GetRay(u, v);
                pixel_color += RayTracer::CalcRayColor(ray, scene.entities_, settings_.quality_settings_.max_bounces_);
            }

            // Calculate final color values by averaging all the samples
            pixel_color /= settings_.quality_settings_.samples_per_pixel_;

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

        if (j == 0)
        {
            // Break out before overflow
            break;
        }
    }

    image.Save(settings_.output_settings_.output_name_.c_str());
    LOG("Done! Saved output image as '{}'", settings_.output_settings_.output_name_);
}
