#pragma once
#include "Camera.h"
#include "Hittable.h"

struct Scene
{
    static inline const Vec3 WORLD_FORWARD = Vec3(0.0f, 0.0f, -1.0f);
    static inline const Vec3 WORLD_RIGHT = Vec3(1.0f, 0.0f, 0.0f);
    static inline const Vec3 WORLD_UP = Vec3(0.0f, 1.0f, 0.0f);

    Camera camera_;
    HittableList entities_;

    static Scene CreateBunnyScene();
    static Scene CreateCubeScene();
    static Scene CreateSpheresScene();
};

