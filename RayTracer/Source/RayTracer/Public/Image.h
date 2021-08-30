#pragma once
#include "Vector.h"

/**
*    Data container for pixel values with RGBA components as uint8
*/
struct PixelData
{
    PixelData() 
    {
    }

    PixelData(uint8 r, uint8 g, uint8 b, uint8 a)
        : r_(r), g_(g), b_(b), a_(a)
    {
    }

    uint8 r_;
    uint8 g_;
    uint8 b_;
    uint8 a_;
};

/**
*   A PNG image - Thin wrapper around stb image writer.
*   Pixels are saved in a one dimensional array, row by row.
*/
class Image
{
public:
    Image(size_t width, size_t height);
    ~Image();

    void SetPixel(size_t x, size_t y, Color color);

    void Save(const char* path);

    size_t GetWidth() const { return width_; }
    size_t GetHeight() const { return height_; }

private:
    size_t width_ = 0;
    size_t height_ = 0;
    PixelData* data_ = nullptr;
};
