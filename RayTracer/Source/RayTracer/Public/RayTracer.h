#pragma once
#include "Ray.h"
#include "Hittable.h"
#include "Scene.h"

struct RenderQualitySettings
{
    uint32 samples_per_pixel_ = 50;
    uint32 max_bounces_ = 100;
};

struct RenderOutputSettings
{
    String output_name_ = "output.png";
    float aspect_ratio_ = 16.0f / 9.0f;
    size_t image_width_ = 128;
    size_t image_height_ = static_cast<size_t>(image_width_ / aspect_ratio_);

    void SetOutputSize(size_t image_width, float aspect_ratio)
    {
        aspect_ratio_ = aspect_ratio;
        image_width_ = image_width;
        image_height_ = static_cast<size_t>(image_width / aspect_ratio);
    }
};

struct RayTracerSettings
{
    RenderQualitySettings quality_settings_;
    RenderOutputSettings output_settings_;
};

class RayTracer
{
public:
    /**
    *    Shoots a ray into the scene and calculates its color.
    *    Rays may be reflected and in turn call this function recursively to figure out the final color.
    *    
    *    @param r   Ray we use to check intersections
    *    @param scene_objects   Objects in the scene we check for intersections
    *    @param num_bounces Maximum number of times the ray can bounce off objects in the scene
    *    @return The final color of the ray after it bounced off the objects in the scene
    */
    static Color CalcRayColor(const Ray& r, const IHittable& scene_objects, uint32 num_bounces);

    RayTracer(const RayTracerSettings& settings)
        : settings_(settings)
    {
    }

    void Trace(const Scene& scene);

private:

    RayTracerSettings settings_;
};
