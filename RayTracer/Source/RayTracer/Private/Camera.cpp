#include "Camera.h"

Camera::Camera(float aspect_ratio, float focal_length)
    : aspect_ratio_(aspect_ratio)
    , focal_length_(focal_length)
{
    viewport_width_ = aspect_ratio_ * viewport_height_;
    horizontal_axis_ = Vec3(viewport_width_, 0.0f, 0.0f);
    vertical_axis_ = Vec3(0.0f, viewport_height_, 0.0f);
    lower_left_corner_ = camera_pos_ - horizontal_axis_ * 0.5f - vertical_axis_ * 0.5f - Vec3(0.0f, 0.0f, focal_length_);
}

Ray Camera::GetRay(float u, float v) const
{
    const Vec3 ray_direction = lower_left_corner_ + u * horizontal_axis_ + v * vertical_axis_ - camera_pos_;
    return Ray(camera_pos_, ray_direction);
}
