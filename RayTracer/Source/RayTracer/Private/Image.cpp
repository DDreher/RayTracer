#include "Image.h"

#include "stb/stb_image_write.h"

Image::Image(size_t width, size_t height)
    : width_(width), height_(height)
{
    data_ = new PixelData[width * height];
}

Image::~Image()
{
    delete[] data_;
    data_ = nullptr;
}

void Image::SetPixel(size_t x, size_t y, Color color)
{
    CHECK(x >= 0 && x < GetWidth());
    CHECK(y >= 0 && y < GetHeight());

    // Convert into [0, 255] range
    uint8 r = static_cast<uint32>(256.0f * Clamp(color.x_, 0.0f, 0.999f));
    uint8 g = static_cast<uint32>(256.0f * Clamp(color.y_, 0.0f, 0.999f));
    uint8 b = static_cast<uint32>(256.0f * Clamp(color.z_, 0.0f, 0.999f));
    uint8 a = 255;

    data_[x + y * GetWidth()] = { r, g, b, a };
}

void Image::Save(const char* path)
{
    static const int bytes_per_row = static_cast<int>(GetWidth() * sizeof(PixelData));
    static const int num_components = 4;    // rgba
    int result = stbi_write_png(path, static_cast<int>(GetWidth()), static_cast<int>(GetHeight()), num_components, static_cast<void*>(data_), bytes_per_row);
    assert(result != 0);
}
