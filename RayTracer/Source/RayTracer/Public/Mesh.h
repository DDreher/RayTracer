#pragma once
#include "Hittable.h"

struct MeshData
{
    static MeshData Load(const String& asset_path);

    Array<uint32> indices;
    Array<Vec3> vertices;
    Array<Vec3> normals;
};

struct CubeMeshData : public MeshData
{
    CubeMeshData()
    {
        indices = {
            // front
            0,  1,  2,
            0,  2,  3,
            // back
            4,  5,  6,
            4,  6,  7,
            // top
            8,  9, 10,
            8, 10, 11,
            // bottom
            12, 13, 14,
            12, 14, 15,
            // left
            16, 17, 18,
            16, 18, 19,
            // right
            20, 21, 22,
            20, 22, 23
        };

        vertices =
        {
            // front
            Vec3(-1.0f, -1.0f,  -1.0f),
            Vec3(-1.0f,  1.0f,  -1.0f),
            Vec3(1.0f,  1.0f,   -1.0f),
            Vec3(1.0f, -1.0f,   -1.0f),
            // back
            Vec3(-1.0f, -1.0f, 1.0f),
            Vec3(1.0f, -1.0f, 1.0f),
            Vec3(1.0f,  1.0f, 1.0f),
            Vec3(-1.0f,  1.0f, 1.0f),
            // top
            Vec3(-1.0f, 1.0f, -1.0f),
            Vec3(-1.0f, 1.0f,  1.0f),
            Vec3(1.0f, 1.0f,  1.0f),
            Vec3(1.0f, 1.0f, -1.0f),
            // bottom
            Vec3(-1.0f, -1.0f, -1.0f),
            Vec3(1.0f, -1.0f, -1.0f),
            Vec3(1.0f, -1.0f,  1.0f),
            Vec3(-1.0f, -1.0f,  1.0f),
            // left
            Vec3(-1.0f, -1.0f,  1.0f),
            Vec3(-1.0f,  1.0f,  1.0f),
            Vec3(-1.0f,  1.0f, -1.0f),
            Vec3(-1.0f, -1.0f, -1.0f),
            // right
            Vec3(1.0f, -1.0f, -1.0f),
            Vec3(1.0f,  1.0f, -1.0f),
            Vec3(1.0f,  1.0f,  1.0f),
            Vec3(1.0f, -1.0f,  1.0f)
        };

        normals =
        {
            // front
            Vec3(-1.0f, -1.0f,  -1.0f),
            Vec3(-1.0f,  1.0f,  -1.0f),
            Vec3(1.0f,  1.0f,   -1.0f),
            Vec3(1.0f, -1.0f,   -1.0f),
            // back
            Vec3(-1.0f, -1.0f, 1.0f),
            Vec3(1.0f, -1.0f, 1.0f),
            Vec3(1.0f,  1.0f, 1.0f),
            Vec3(-1.0f,  1.0f, 1.0f),
            // top
            Vec3(-1.0f, 1.0f, -1.0f),
            Vec3(-1.0f, 1.0f,  1.0f),
            Vec3(1.0f, 1.0f,  1.0f),
            Vec3(1.0f, 1.0f, -1.0f),
            // bottom
            Vec3(-1.0f, -1.0f, -1.0f),
            Vec3(1.0f, -1.0f, -1.0f),
            Vec3(1.0f, -1.0f,  1.0f),
            Vec3(-1.0f, -1.0f,  1.0f),
            // left
            Vec3(-1.0f, -1.0f,  1.0f),
            Vec3(-1.0f,  1.0f,  1.0f),
            Vec3(-1.0f,  1.0f, -1.0f),
            Vec3(-1.0f, -1.0f, -1.0f),
            // right
            Vec3(1.0f, -1.0f, -1.0f),
            Vec3(1.0f,  1.0f, -1.0f),
            Vec3(1.0f,  1.0f,  1.0f),
            Vec3(1.0f, -1.0f,  1.0f)
        };
    }
};

class Mesh : public HittableList
{
public:
    Mesh() {}
    Mesh(const Vec3& position, float scale, const SharedPtr<IMaterial>& material, const String& asset_path);

private:
    MeshData mesh_data_;
    Vec3 position_;
    float scale_ = 1.0f;
    SharedPtr<IMaterial> material_;
};
