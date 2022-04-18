#include "RayTracer.h"
#include "Scene.h"

int main()
{
    Log::Init("RAYTRACER");

    // Set up settings
    RenderOutputSettings output_settings;
    output_settings.SetOutputSize(512, 16.0f / 9.0f);

    RenderQualitySettings quality_settings;
    quality_settings.samples_per_pixel_ = 50;
    quality_settings.max_bounces_ = 100;

    RayTracerSettings settings;
    settings.output_settings_ = output_settings;
    settings.quality_settings_ = quality_settings;

    // Set up scene
    Scene scene = Scene::CreateBunnyScene();

    // Do the raytracing
    RayTracer raytracer(settings);
    raytracer.Trace(scene);
}
