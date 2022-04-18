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

    // Figure out tasks to be done
    uint32 num_available_threads = static_cast<uint32>(std::thread::hardware_concurrency() - 2);  // -2 to keep everything responsible.
    uint32 num_worker_threads = Clamp<uint32>(settings_.num_threads_, 1, num_available_threads);

    const size_t tile_width = image.GetWidth() / num_worker_threads;
    const size_t tile_height = image.GetHeight() / num_worker_threads;
    const size_t num_tiles_x = (image.GetWidth() + tile_width - 1) / tile_width;
    const size_t num_tiles_y = (image.GetHeight() + tile_height - 1) / tile_height;

    CHECK(num_tiles_x * tile_width >= image_width);
    CHECK(num_tiles_y * tile_height >= image_height);

    Array<TileDescriptor> tile_descriptors;
    for(size_t tile_y=0; tile_y < num_tiles_y; ++tile_y)
    {
        for (size_t tile_x = 0; tile_x < num_tiles_x; ++tile_x)
        {
            tile_descriptors.emplace_back(tile_x*tile_width, tile_y*tile_height, tile_width, tile_height);
        }
    }

    size_t descriptors_per_thread = (tile_descriptors.size() + num_worker_threads -1) / num_worker_threads;

    LOG("Start path tracing on {} threads", num_worker_threads);

    Array<std::thread> worker_threads;
    for(uint32 i=0; i<num_worker_threads; ++i)
    {
            const size_t start_offset = i * descriptors_per_thread;
            const size_t end_offset = std::min(i * descriptors_per_thread + descriptors_per_thread, tile_descriptors.size());
            Array<TileDescriptor> tasks = Array<TileDescriptor>(tile_descriptors.begin() + start_offset, tile_descriptors.begin() + end_offset);

            worker_threads.push_back(
                std::thread([this, &scene, &image, tasks](){
                    this->TraceTile(scene, image, tasks);
                })
            );
    }

    // Wait until all worker threads have finished
    for(auto& t : worker_threads)
    {
        t.join();
    }

    // Finally save rendered image
    image.Save(settings_.output_settings_.output_name_.c_str());
    LOG("Done! Saved output image as '{}'", settings_.output_settings_.output_name_);
}

void RayTracer::TraceTile(const Scene& scene, Image& image, Array<TileDescriptor> tasks)
{
    for(const auto& task : tasks)
    {
        size_t end_y = task.start_y + task.tile_height;
        size_t end_x = task.start_x + task.tile_width;

        // Shoot a ray into the scene for each pixel of the tile
        for (size_t y = task.start_y; y < end_y; ++y)
        {
            for (size_t x = task.start_x; x < end_x; ++x)
            {
                if(y >= image.GetHeight() || x >= image.GetWidth())
                {
                    continue;
                }

                Color pixel_color;

                // Calculate multiple samples per pixel for antialiasing
                for (uint32_t sample_idx = 0; sample_idx < settings_.quality_settings_.samples_per_pixel_; ++sample_idx)
                {
                    // Coordinates in viewport space
                    float u = static_cast<float>(x + Rand()) / (image.GetWidth() - 1.0f);
                    float v = static_cast<float>(y + Rand()) / (image.GetHeight() - 1.0f);

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
                size_t pixel_x = x;
                size_t pixel_y = image.GetHeight() - 1 - y;
                image.SetPixel(pixel_x, pixel_y, pixel_color);
            }
        }
    }
}
