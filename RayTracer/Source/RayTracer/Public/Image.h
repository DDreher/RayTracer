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
    /**
     * Creates an empty bitmap of size width x height x 4 (RGBA)
     */
    Image(size_t width, size_t height);

    /**
     * Loads a RGBA bitmap from path
     */
    Image(const String& path);
    ~Image();

    Color GetPixel(size_t x, size_t y) const;
    Color GetPixel(float u, float v) const;
    void SetPixel(size_t x, size_t y, Color color);

    /**
    *   Saves the image in png format at the given path relative to the working directory.
    *   e.g: "output.png" will be saved at `{working_dir}/output.png`.
    *   
    *   @param path output path (including filename and extension) relative to the working directory.
    */
    void Save(const char* path);

    size_t GetWidth() const { return width_; }
    size_t GetHeight() const { return height_; }

private:
    size_t width_ = 0;
    size_t height_ = 0;
    PixelData* data_ = nullptr;
};
