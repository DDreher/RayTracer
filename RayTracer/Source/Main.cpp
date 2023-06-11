#include "RayTracer.h"
#include "Scene.h"

int main()
{
    Log::Init("RAYTRACER");

    // Set up settings
    RenderOutputSettings output_settings;
    output_settings.SetOutputSize(1024, 16.0f / 9.0f);

    RenderQualitySettings quality_settings;
    quality_settings.samples_per_pixel_ = 100;
    quality_settings.max_bounces_ = 100;

    RayTracerSettings settings
    { 
        .quality_settings_ = quality_settings,
        .output_settings_ = output_settings,
        .num_threads_ = UINT_MAX
    };

    // Set up scene
    Scene scene = Scene::CreateSpheresScene();

    // Do the raytracing
    RayTracer raytracer(settings);
    raytracer.Trace(scene);
}
