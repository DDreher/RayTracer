#include "Camera.h"

Camera::Camera()
{
    UpdateViewport();
}

Camera::Camera(const Vec3& position, const Vec3& look_at, const Vec3& up, const CameraAttributes& attributes)
    : position_(position)
    , attributes_(attributes)
{
    cam_forward_ = MakeUnitVec(position_ - look_at);
    cam_right_ = MakeUnitVec(Cross(up, cam_forward_));
    cam_up_ = Cross(cam_forward_, cam_right_);

    UpdateViewport();
}

Ray Camera::GetRay(float u, float v) const
{
    // Calculate offset on the lense for defocus blur
    const Vec3 point_on_lense = attributes_.lens_radius_ * Vec3::GetRandomPointInUnitDisk();
    const Vec3 offset = cam_right_ * point_on_lense.x_ + cam_up_ * point_on_lense.y_;
    const Vec3 ray_direction = viewport_lower_left_corner_ + u * horizontal_axis_ + v * vertical_axis_ - position_ - offset;
    return Ray(position_ + offset, ray_direction);
}

void Camera::UpdateViewport()
{
    float theta = DegToRads(attributes_.vertical_fov_degrees_);
    float half_viewport_height = tanf(theta * 0.5f);
    viewport_height_ = 2.0f * half_viewport_height;
    viewport_width_ = attributes_.aspect_ratio_ * viewport_height_;

    horizontal_axis_ = attributes_.focus_distance_ * viewport_width_ * cam_right_;
    vertical_axis_ = attributes_.focus_distance_ * viewport_height_ * cam_up_;
    viewport_lower_left_corner_ = position_ - horizontal_axis_ * 0.5f - vertical_axis_ * 0.5f - attributes_.focus_distance_ * cam_forward_;

    attributes_.lens_radius_ = attributes_.aperture_ * 0.5f;
}
