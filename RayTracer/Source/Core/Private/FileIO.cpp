#include "FileIO.h"

#include <fstream>

Array<char> FileIO::ReadFile(const String& filename)
{
    // ate: Start reading at the end of the file -> we can use the read position to determine the file size and allocate a buffer
    // binary : Read the file as binary file (avoid text transformations)
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    CHECK(file.is_open())

    size_t file_size = (size_t)file.tellg();
    std::vector<char> buffer(file_size);

    file.seekg(0);
    file.read(buffer.data(), file_size);
    file.close();

    return buffer;
}