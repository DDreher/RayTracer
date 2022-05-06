#pragma once

struct Vertex
{
    Vec3 position_;
    std::optional<Vec3> normal_;
    std::optional<Vec3> tex_coords_;
};