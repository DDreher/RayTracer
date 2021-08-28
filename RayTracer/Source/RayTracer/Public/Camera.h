#pragma once
#include "Ray.h"
#include "Vector.h"

class Camera
{
public:
    Camera() = default;
    Camera(float aspect_ratio, float focal_length);

    Ray GetRay(float u, float v) const;

private:
    // Virtual Viewport
    float aspect_ratio_ = 16.0f / 9.0f;
    float viewport_height_ = 2.0f;
    float viewport_width_ = aspect_ratio_ * viewport_height_;
    float focal_length_ = 1.0f; // distance between the projection plane and the projection point (NOT focus distance!)
    Vec3 horizontal_axis_ = Vec3(viewport_width_, 0.0f, 0.0f);
    Vec3 vertical_axis_ = Vec3(0.0f, viewport_height_, 0.0f);

    Point3 camera_pos_;
    Point3 lower_left_corner_ = camera_pos_ - horizontal_axis_ * 0.5f - vertical_axis_ * 0.5f - Vec3(0.0f, 0.0f, focal_length_);
};
