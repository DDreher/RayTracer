#pragma once
#include "Ray.h"
#include "Vector.h"

struct CameraAttributes
{
    float aspect_ratio_ = 16.0f / 9.0f;
    float focal_length_ = 1.0f; // distance between the projection point and the image plane
    float vertical_fov_degrees_ = 40.0f;
    float focus_distance_ = 1.0f;   // distance between the lens and the film/sensor
    float aperture_ = 0.0f; // Hole to control how big the lens is effectively. Bigger -> More defocus blur. 0 -> No blur (Perfect sensor).
    float lens_radius_ = 0.0f;   // Automatically calculated.
};

class Camera
{
public:
    Camera();
    Camera(const Vec3& position, const Vec3& look_at, const Vec3& world_up, const CameraAttributes& attributes);

    Ray GetRay(float u, float v) const;

private:
    void UpdateViewport();

    // Camera properties
    Vec3 position_;

    Vec3 cam_forward_;
    Vec3 cam_right_;
    Vec3 cam_up_;

    CameraAttributes attributes_;

    // Virtual Viewport
    float viewport_height_;
    float viewport_width_;
    Vec3 horizontal_axis_;
    Vec3 vertical_axis_;
    Point3 viewport_lower_left_corner_;
};
