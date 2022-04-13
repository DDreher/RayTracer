#pragma once
#include "Core.h"

struct FileIO
{
    static Array<char> ReadFile(const String& filename);
};