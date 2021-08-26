#include <algorithm>
#include <array>
#include <assert.h>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <set>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "Log.h"

#define LOG(...) Log::PrintLine(__VA_ARGS__)

#ifdef NDEBUG
    #define DEBUG_BREAK()
    #define CHECK(expression)
#else
    #define DEBUG_BREAK() __debugbreak()
    #define CHECK(expression) if(!(expression)) { DEBUG_BREAK(); }
#endif

// Type aliases
using uint8 = uint8_t;
using int8 = int8_t;
using uint16 = uint16_t;
using int16 = int16_t;
using uint32 = uint32_t;
using int32 = int32_t;
using uint64 = uint64_t;
using int64 = int64_t;
