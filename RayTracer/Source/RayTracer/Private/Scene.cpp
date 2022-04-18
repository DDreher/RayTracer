#include "Camera.h"
#include "Mesh.h"
#include "Scene.h"
#include "Sphere.h"
#include "MaterialLambertian.h"
#include "MaterialMetal.h"
#include "MaterialDielectric.h"

Scene Scene::CreateBunnyScene()
{
    Scene out_scene;

    // Set up camera
    Vec3 camera_pos = Vec3(-2.0f, 0.7f, .75f);
    Vec3 camera_look_at = Vec3(0.0f, 0.0f, -1.0f);

    CameraAttributes camera_attributes;
    camera_attributes.vertical_fov_degrees_ = 45.0f;
    camera_attributes.focus_distance_ = (camera_pos - Vec3(-1.0f, 0.0f, -1.0f)).Length();
    camera_attributes.aperture_ = 0.025f;

    out_scene.camera_ = Camera(camera_pos, camera_look_at, Scene::WORLD_UP, camera_attributes);

    // Set up entities
    SharedPtr<IMaterial> material_diffuse = MakeShared<Lambertian>(Color(0.9f, 0.1f, 0.1f));
    SharedPtr<IMaterial> material_ground = MakeShared<Lambertian>(Color(107.0f / 255.0f, 142.0f / 255.0f, 35.0f / 255.0f));
    SharedPtr<IMaterial> material_metal_rougher = MakeShared<Metal>(Color(0.39f, 0.58f, 0.92f), 0.8f);
    SharedPtr<IMaterial> material_metal_smooth = MakeShared<Metal>(Color(212.0f / 255.0f, 175.0f / 255.0f, 55.0f / 255.0f), 0.1f);
    SharedPtr<IMaterial> material_glass = MakeShared<Dielectric>(1.5f);

    out_scene.entities_.Add(MakeShared<Sphere>(Point3(0.0f, -100.5f, -1.0f), 100.0f, material_ground));
    out_scene.entities_.Add(MakeShared<Sphere>(Point3(0.0f, 0.0f, -1.0f), 0.5f, material_glass));
    out_scene.entities_.Add(MakeShared<Sphere>(Point3(0.0f, 0.0f, -1.0f), -0.4f, material_glass));   // We can fake hollow glass spheres by using a negative radius
                                                                                                    // -> surface normals point inwards
    out_scene.entities_.Add(MakeShared<Sphere>(Point3(1.0f, 0.0f, -1.0f), 0.5f, material_metal_rougher));
    out_scene.entities_.Add(MakeShared<Sphere>(Point3(2.0f, 0.0f, -1.0f), 0.5f, material_diffuse));

    out_scene.entities_.Add(MakeShared<Mesh>(Vec3(-.75f, 0.1f, -1.0f), 0.15f, material_metal_smooth, "Assets/Meshes/bunny.fbx"));

    return out_scene;
}

Scene Scene::CreateCubeScene()
{
    Scene out_scene;

    // Set up camera
    Vec3 camera_pos = Vec3(-2.0f, 0.7f, .75f);
    Vec3 camera_look_at = Vec3(0.0f, 0.0f, -1.0f);

    CameraAttributes camera_attributes;
    camera_attributes.vertical_fov_degrees_ = 45.0f;
    camera_attributes.focus_distance_ = (camera_pos - Vec3(.0f, .4f * .5f, -1.0f)).Length();
    camera_attributes.aperture_ = 0.025f;

    out_scene.camera_ = Camera(camera_pos, camera_look_at, Scene::WORLD_UP, camera_attributes);

    // Set up entities
    SharedPtr<IMaterial> material_diffuse = MakeShared<Lambertian>(Color(0.9f, 0.1f, 0.1f));
    SharedPtr<IMaterial> material_ground = MakeShared<Lambertian>(Color(107.0f / 255.0f, 142.0f / 255.0f, 35.0f / 255.0f));
    SharedPtr<IMaterial> material_metal_rougher = MakeShared<Metal>(Color(0.39f, 0.58f, 0.92f), 0.8f);
    SharedPtr<IMaterial> material_metal_smooth = MakeShared<Metal>(Color::GOLD, 0.05f);
    SharedPtr<IMaterial> material_glass = MakeShared<Dielectric>(1.5f);

    MeshData cube_data = CubeMeshData();

    out_scene.entities_.Add(MakeShared<Mesh>(Vec3(0.0f, -25.0f, 0.0f), 50.0f, material_ground, cube_data));

    //out_scene.entities_.Add(MakeShared<Sphere>(Point3(0.0f, -100.5f, -1.0f), 100.0f, material_ground));

    float scale = .1f;
    out_scene.entities_.Add(MakeShared<Mesh>(Vec3(-1.35f, scale * .5f, -0.0f), scale, material_glass, cube_data));
    out_scene.entities_.Add(MakeShared<Mesh>(Vec3(-1.35f, scale * .5f, -1.0f), scale, material_glass, cube_data));
    out_scene.entities_.Add(MakeShared<Mesh>(Vec3(-1.35f, scale * .5f, -2.0f), scale, material_glass, cube_data));

    scale = .2f;
    out_scene.entities_.Add(MakeShared<Mesh>(Vec3(-1.0f, scale * .5f, -0.0f), scale, material_diffuse, cube_data));
    out_scene.entities_.Add(MakeShared<Mesh>(Vec3(-1.0f, scale * .5f, -1.0f), scale, material_diffuse, cube_data));
    out_scene.entities_.Add(MakeShared<Mesh>(Vec3(-1.0f, scale * .5f, -2.0f), scale, material_diffuse, cube_data));

    scale = .3f;
    out_scene.entities_.Add(MakeShared<Mesh>(Vec3(-.5f, scale * .5f, -0.0f), scale, material_metal_smooth, cube_data));
    out_scene.entities_.Add(MakeShared<Mesh>(Vec3(-.5f, scale * .5f, -1.0f), scale, material_metal_smooth, cube_data));
    out_scene.entities_.Add(MakeShared<Mesh>(Vec3(-.5f, scale * .5f, -2.0f), scale, material_metal_smooth, cube_data));

    scale = .4f;
    out_scene.entities_.Add(MakeShared<Mesh>(Vec3(.0f, scale * .5f, -0.0f), scale, material_glass, cube_data));
    out_scene.entities_.Add(MakeShared<Mesh>(Vec3(.0f, scale * .5f, -1.0f), scale, material_glass, cube_data));
    out_scene.entities_.Add(MakeShared<Mesh>(Vec3(.0f, scale * .5f, -2.0f), scale, material_glass, cube_data));

    scale = .5f;
    out_scene.entities_.Add(MakeShared<Mesh>(Vec3(.75f, scale * .5f, -0.0f), scale, material_metal_rougher, cube_data));
    out_scene.entities_.Add(MakeShared<Mesh>(Vec3(.75f, scale * .5f, -1.0f), scale, material_metal_rougher, cube_data));
    out_scene.entities_.Add(MakeShared<Mesh>(Vec3(.75f, scale * .5f, -2.0f), scale, material_metal_rougher, cube_data));


    return out_scene;
}
