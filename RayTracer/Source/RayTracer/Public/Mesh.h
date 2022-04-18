#pragma once
#include "Hittable.h"

struct MeshData
{
    static MeshData Load(const String& asset_path);

    Array<uint32> indices_;
    Array<Vec3> vertices_;
    Array<Vec3> normals_;
};

struct CubeMeshData : public MeshData
{
    CubeMeshData()
    {
        indices_ = {
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

        vertices_ =
        {
            // front
            Vec3(-1.0f, -0.5f,  -0.5f),
            Vec3(-0.5f,  0.5f,  -0.5f),
            Vec3(0.5f,  0.5f,   -0.5f),
            Vec3(0.5f, -0.5f,   -0.5f),
            // back
            Vec3(-0.5f, -0.5f, 0.5f),
            Vec3(0.5f, -0.5f, 0.5f),
            Vec3(0.5f,  0.5f, 0.5f),
            Vec3(-0.5f,  0.5f, 0.5f),
            // top
            Vec3(-0.5f, 0.5f, -0.5f),
            Vec3(-0.5f, 0.5f,  0.5f),
            Vec3(0.5f, 0.5f,  0.5f),
            Vec3(0.5f, 0.5f, -0.5f),
            // bottom
            Vec3(-0.5f, -0.5f, -0.5f),
            Vec3(0.5f, -0.5f, -0.5f),
            Vec3(0.5f, -0.5f,  0.5f),
            Vec3(-0.5f, -0.5f,  0.5f),
            // left
            Vec3(-0.5f, -0.5f,  0.5f),
            Vec3(-0.5f,  0.5f,  0.5f),
            Vec3(-0.5f,  0.5f, -0.5f),
            Vec3(-0.5f, -0.5f, -0.5f),
            // right
            Vec3(0.5f, -0.5f, -0.5f),
            Vec3(0.5f,  0.5f, -0.5f),
            Vec3(0.5f,  0.5f,  0.5f),
            Vec3(0.5f, -0.5f,  0.5f)
        };

        normals_ =
        {
            // front
            Vec3(0.0f, 0.0f, 1.0f),
            Vec3(0.0f, 0.0f, 1.0f),
            Vec3(0.0f, 0.0f, 1.0f),
            Vec3(0.0f, 0.0f, 1.0f),
            // back
            Vec3(0.0f, 0.0f, -1.0f),
            Vec3(0.0f, 0.0f, -1.0f),
            Vec3(0.0f, 0.0f, -1.0f),
            Vec3(0.0f, 0.0f, -1.0f),
            // top
            Vec3(0.0f, 1.0f, 0.0f),
            Vec3(0.0f, 1.0f, 0.0f),
            Vec3(0.0f, 1.0f, 0.0f),
            Vec3(0.0f, 1.0f, 0.0f),
            // bottom
            Vec3(0.0f, -1.0f, 0.0f),
            Vec3(0.0f, -1.0f, 0.0f),
            Vec3(0.0f, -1.0f, 0.0f),
            Vec3(0.0f, -1.0f, 0.0f),
            // left
            Vec3(-1.0f, 0.0f, 0.0f),
            Vec3(-1.0f, 0.0f, 0.0f),
            Vec3(-1.0f, 0.0f, 0.0f),
            Vec3(-1.0f, 0.0f, 0.0f),
            // right
            Vec3(1.0f, 0.0f, 0.0f),
            Vec3(1.0f, 0.0f, 0.0f),
            Vec3(1.0f, 0.0f, 0.0f),
            Vec3(1.0f, 0.0f, 0.0f),
        };
    }
};

class Mesh : public HittableList
{
public:
    Mesh() {}
    Mesh(const Vec3& position, float scale, const SharedPtr<IMaterial>& material, const String& asset_path);
    Mesh(const Vec3& position, float scale, const SharedPtr<IMaterial>& material, const MeshData& mesh_data);

private:
    MeshData mesh_data_;
    Vec3 position_;
    float scale_ = 1.0f;
    SharedPtr<IMaterial> material_;
};
