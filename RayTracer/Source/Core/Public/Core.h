#include <algorithm>
#include <array>
#include <assert.h>
#include <cstdint>
#include <cstdlib>
#include <deque>
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <queue>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "Log.h"
#include "MathUtils.h"

#define LOG(...) Log::PrintLine(__VA_ARGS__)

#ifdef NDEBUG
    #define DEBUG_BREAK()
    #define CHECK(expression)
#else
    #define DEBUG_BREAK() __debugbreak()
    #define CHECK(expression) if(!(expression)) { DEBUG_BREAK(); }
#endif

// Type aliases

//~ Unsigned base types
using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

//~ Signed base types
using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;

//~ Smart Pointers
template<typename T>
using UniquePtr = std::unique_ptr<T>;

template<typename T, typename ... Args>
constexpr UniquePtr<T> MakeUnique(Args&& ... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using SharedPtr = std::shared_ptr<T>;

template<typename T, typename ... Args>
constexpr SharedPtr<T> MakeShared(Args&& ... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T>
using WeakPtr = std::weak_ptr<T>;

//~ Array Type
template<typename T>
using Array = std::vector<T>;

//~ Hashmap Type
template<typename T, typename T2>
using Map = std::unordered_map<T, T2>;

//~ Deque Type
template<typename T>
using Deque = std::deque<T>;

//~ Queue Type
template<typename T>
using Queue = std::queue<T>;

//~ String Type
using String = std::string;
