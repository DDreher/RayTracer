#pragma once
#include "Hittable.h"

struct MeshData
{
    static MeshData Load(const String& asset_path);

    Array<uint32> indices_;
    Array<Vec4> vertices_;
    Array<Vec4> normals_;
    Array<Vec3> tex_coords_;
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
            Vec4(-.5f, -0.5f, -0.5f, 1.0f),
            Vec4(-0.5f,  0.5f, -0.5f, 1.0f),
            Vec4(0.5f,  0.5f, -0.5f, 1.0f),
            Vec4(0.5f, -0.5f, -0.5f, 1.0f),
            // back
            Vec4(-0.5f, -0.5f, 0.5f, 1.0f),
            Vec4(0.5f, -0.5f, 0.5f , 1.0f),
            Vec4(0.5f,  0.5f, 0.5f , 1.0f),
            Vec4(-0.5f,  0.5f, 0.5f, 1.0f),
            // top
            Vec4(-0.5f, 0.5f, -0.5f, 1.0f),
            Vec4(-0.5f, 0.5f,  0.5f, 1.0f),
            Vec4(0.5f, 0.5f,  0.5f , 1.0f),
            Vec4(0.5f, 0.5f, -0.5f , 1.0f),
            // bottom
            Vec4(-0.5f, -0.5f, -0.5f, 1.0f),
            Vec4(0.5f, -0.5f, -0.5f , 1.0f),
            Vec4(0.5f, -0.5f, 0.5f  , 1.0f),
            Vec4(-0.5f, -0.5f, 0.5f , 1.0f),
            // left
            Vec4(-0.5f, -0.5f, 0.5f , 1.0f),
            Vec4(-0.5f,  0.5f, 0.5f , 1.0f),
            Vec4(-0.5f,  0.5f, -0.5f, 1.0f),
            Vec4(-0.5f, -0.5f, -0.5f, 1.0f),
            // right
            Vec4(0.5f, -0.5f, -0.5f, 1.0f),
            Vec4(0.5f,  0.5f, -0.5f, 1.0f),
            Vec4(0.5f,  0.5f, 0.5f , 1.0f),
            Vec4(0.5f, -0.5f, 0.5f , 1.0f)
        };

        normals_ =
        {
            // front
            Vec4(0.0f, 0.0f, 1.0f, 0.0f),
            Vec4(0.0f, 0.0f, 1.0f, 0.0f),
            Vec4(0.0f, 0.0f, 1.0f, 0.0f),
            Vec4(0.0f, 0.0f, 1.0f, 0.0f),
            // back
            Vec4(0.0f, 0.0f, -1.0f, 0.0f),
            Vec4(0.0f, 0.0f, -1.0f, 0.0f),
            Vec4(0.0f, 0.0f, -1.0f, 0.0f),
            Vec4(0.0f, 0.0f, -1.0f, 0.0f),
            // top
            Vec4(0.0f, 1.0f, 0.0f, 0.0f),
            Vec4(0.0f, 1.0f, 0.0f, 0.0f),
            Vec4(0.0f, 1.0f, 0.0f, 0.0f),
            Vec4(0.0f, 1.0f, 0.0f, 0.0f),
            // bottom
            Vec4(0.0f, -1.0f, 0.0f, 0.0f),
            Vec4(0.0f, -1.0f, 0.0f, 0.0f),
            Vec4(0.0f, -1.0f, 0.0f, 0.0f),
            Vec4(0.0f, -1.0f, 0.0f, 0.0f),
            // left
            Vec4(-1.0f, 0.0f, 0.0f, 0.0f),
            Vec4(-1.0f, 0.0f, 0.0f, 0.0f),
            Vec4(-1.0f, 0.0f, 0.0f, 0.0f),
            Vec4(-1.0f, 0.0f, 0.0f, 0.0f),
            // right
            Vec4(1.0f, 0.0f, 0.0f, 0.0f),
            Vec4(1.0f, 0.0f, 0.0f, 0.0f),
            Vec4(1.0f, 0.0f, 0.0f, 0.0f),
            Vec4(1.0f, 0.0f, 0.0f, 0.0f),
        };

        tex_coords_ =
        {
            // front
            Vec3(0.0f, 1.0f, 0.0f),
            Vec3(0.0f, 0.0f, 0.0f),
            Vec3(1.0f, 0.0f, 0.0f),
            Vec3(1.0f, 1.0f, 0.0f),
            // back
            Vec3(1.0f, 1.0f, 0.0f),
            Vec3(0.0f, 1.0f, 0.0f),
            Vec3(0.0f, 0.0f, 0.0f),
            Vec3(1.0f, 0.0f, 0.0f),
            // top
            Vec3(0.0f, 1.0f, 0.0f),
            Vec3(0.0f, 0.0f, 0.0f),
            Vec3(1.0f, 0.0f, 0.0f),
            Vec3(1.0f, 1.0f, 0.0f),
            // botttom
            Vec3(1.0f, 1.0f, 0.0f),
            Vec3(0.0f, 1.0f, 0.0f),
            Vec3(0.0f, 0.0f, 0.0f),
            Vec3(1.0f, 0.0f, 0.0f),
            // left
            Vec3(0.0f, 1.0f, 0.0f),
            Vec3(0.0f, 0.0f, 0.0f),
            Vec3(1.0f, 0.0f, 0.0f),
            Vec3(1.0f, 1.0f, 0.0f),
            // right
            Vec3(0.0f, 1.0f, 0.0f),
            Vec3(0.0f, 0.0f, 0.0f),
            Vec3(1.0f, 0.0f, 0.0f),
            Vec3(1.0f, 1.0f, 0.0f)
        };
    }
};

class Mesh : public HittableList
{
public:
    Mesh() {}
    Mesh(const Vec3& position, float scale, const Mat4& rotation, const SharedPtr<IMaterial>& material, const String& asset_path);
    Mesh(const Vec3& position, float scale, const Mat4& rotation, const SharedPtr<IMaterial>& material, const MeshData& mesh_data);

    void CreateTriangleListFromMeshData();

    // Begin IHittable
    virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& hit_record) const override;
    // End IHittable

private:
    MeshData mesh_data_;
    Vec3 position_;
    glm::mat4 rotation_ = glm::identity<glm::mat4>();
    float scale_ = 1.0f;
    SharedPtr<IMaterial> material_;
};
