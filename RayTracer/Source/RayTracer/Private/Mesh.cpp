#include "Mesh.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

#include "FileIO.h"
#include "Triangle.h"

MeshData MeshData::Load(const String& asset_path)
{
    MeshData mesh_data;

    Assimp::Importer importer;

    Array<char> bytes = FileIO::ReadFile(asset_path);

    uint32 importer_flags = aiProcessPreset_TargetRealtime_Fast;
    const aiScene* scene = importer.ReadFileFromMemory(bytes.data(), bytes.size(), importer_flags);
    CHECK_MSG(scene != nullptr, "Failed to load mesh from file: {}", asset_path);

    for (uint32 mesh_idx = 0; mesh_idx < scene->mNumMeshes; ++mesh_idx)
    {
        aiMesh* mesh = scene->mMeshes[mesh_idx];
        for (uint32 vertex_id = 0; vertex_id < mesh->mNumVertices; ++vertex_id)
        {
            const aiVector3D& vertex = mesh->mVertices[vertex_id];
            mesh_data.vertices_.push_back({ vertex.x, vertex.y, vertex.z });

            const aiVector3D& normal = mesh->HasNormals() ? mesh->mNormals[vertex_id] : aiVector3D(0.0f, 0.0f, 0.0f);
            mesh_data.normals_.push_back({ normal.x, normal.y, normal.z });

            //const aiVector3D& uv = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][vertex_id] : aiVector3D(0.0f, 0.0f, 0.0f);
            //uvs.push_back({ uv.x, uv.y });
        }

        for (uint32 i = 0; i < mesh->mNumFaces; ++i)
        {
            const aiFace& face = mesh->mFaces[i];
            CHECK(face.mNumIndices == 3);
            mesh_data.indices_.push_back(face.mIndices[0]);
            mesh_data.indices_.push_back(face.mIndices[1]);
            mesh_data.indices_.push_back(face.mIndices[2]);
        }
    }

    return mesh_data;
}

//////////////////////////////////////////////////////////////////////////

Mesh::Mesh(const Vec3& position, float scale, const SharedPtr<IMaterial>& material, const String& asset_path)
    : position_(position), scale_(scale), material_(material)
{
    mesh_data_ = MeshData::Load(asset_path);
    CHECK(mesh_data_.indices_.size() % 3 == 0);

    for (uint32 i = 0; i < mesh_data_.indices_.size(); i+=3)
    {
        uint32 idx0 = mesh_data_.indices_[i];
        uint32 idx1 = mesh_data_.indices_[i+1];
        uint32 idx2 = mesh_data_.indices_[i+2];

        Vertex v0 = { mesh_data_.vertices_[idx0] * scale_ + position_,
                        mesh_data_.normals_[idx0] };
        Vertex v1 = { mesh_data_.vertices_[idx1] * scale_ + position_,
                        mesh_data_.normals_[idx1] };
        Vertex v2 = { mesh_data_.vertices_[idx2] * scale_ + position_,
                                mesh_data_.normals_[idx2] };


        SharedPtr<Triangle> triangle = MakeShared<Triangle>(v0, v1, v2, material_);
        Add(triangle);
    }
}

Mesh::Mesh(const Vec3& position, float scale, const SharedPtr<IMaterial>& material, const MeshData& mesh_data)
    : position_(position), scale_(scale), material_(material), mesh_data_(mesh_data)
{
    CHECK(mesh_data_.indices_.size() % 3 == 0);

    for (uint32 i = 0; i < mesh_data_.indices_.size(); i += 3)
    {
        uint32 idx0 = mesh_data_.indices_[i];
        uint32 idx1 = mesh_data_.indices_[i + 1];
        uint32 idx2 = mesh_data_.indices_[i + 2];

        Vertex v0 = { mesh_data_.vertices_[idx0] * scale_ + position_,
                        mesh_data_.normals_[idx0]};
        Vertex v1 = { mesh_data_.vertices_[idx1] * scale_ + position_,
                        mesh_data_.normals_[idx1] };
        Vertex v2 = { mesh_data_.vertices_[idx2] * scale_ + position_,
                                mesh_data_.normals_[idx2] };


        SharedPtr<Triangle> triangle = MakeShared<Triangle>(v0, v1, v2, material_);
        Add(triangle);
    }
}
