#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

Image::Image(size_t width, size_t height)
    : width_(width), height_(height)
{
    CHECK(width > 0 && height > 0);
    data_ = new PixelData[width * height];
}

Image::Image(const String& path)
{
    CHECK(path.empty() == false);

    int w;
    int h;
    int c;
    stbi_uc* tex_data = stbi_load(path.c_str(), &w, &h, &c, STBI_rgb_alpha);
    CHECK(tex_data != nullptr);
    CHECK(w > 0 && h > 0 && c == 4);

    width_ = w;
    height_ = h;
    data_ = new PixelData[width_ * height_];
    memcpy(data_, tex_data, w * h * c * sizeof(uint8));

    stbi_image_free(tex_data);
}

Image::~Image()
{
    delete[] data_;
    data_ = nullptr;
}

Color Image::GetPixel(size_t x, size_t y) const
{
    CHECK(x >= 0 && x < GetWidth());
    CHECK(y >= 0 && y < GetHeight());
    const PixelData p = data_[x + y * GetWidth()];
    return { p.r_ / 255.0f, p.g_ / 255.0f, p.b_ / 255.0f };
}

Color Image::GetPixel(float u, float v) const
{
    u = glm::clamp(u, 0.0f, 1.0f);
    v = 1.0f - glm::clamp(v, 0.0f, 1.0f);

    size_t x = static_cast<size_t>(u * (GetWidth()-1));
    size_t y = static_cast<size_t>(v * (GetHeight()-1));

    return GetPixel(x, y);
}

void Image::SetPixel(size_t x, size_t y, Color color)
{
    CHECK(x >= 0 && x < GetWidth());
    CHECK(y >= 0 && y < GetHeight());

    // Convert into [0, 255] range
    uint8 r = static_cast<uint32>(256.0f * glm::clamp(color.x, 0.0f, 0.999f));
    uint8 g = static_cast<uint32>(256.0f * glm::clamp(color.y, 0.0f, 0.999f));
    uint8 b = static_cast<uint32>(256.0f * glm::clamp(color.z, 0.0f, 0.999f));
    uint8 a = 255;

    data_[x + y * GetWidth()] = { r, g, b, a };
}

void Image::Save(const char* path)
{
    static const int bytes_per_row = static_cast<int>(GetWidth() * sizeof(PixelData));
    static const int num_components = 4;    // rgba
    int result = stbi_write_png(path, static_cast<int>(GetWidth()), static_cast<int>(GetHeight()), num_components, static_cast<void*>(data_), bytes_per_row);
    CHECK(result != 0);
}
