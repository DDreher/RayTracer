#include "RayTracer.h"

#include "iosfwd"

void WritePixel(std::ostream& out_stream, const Color& color)
{
    // Convert into [0, 255] range
    uint32 r = static_cast<uint32>(255.999 * color.x_);
    uint32 g = static_cast<uint32>(255.999 * color.y_);
    uint32 b = static_cast<uint32>(255.999 * color.z_);
    std::cout << r << ' ' << g << ' ' << b << '\n';
}
