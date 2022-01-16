#pragma once

#include <cstdint>

// Contains stuff predefined in C# but not C++

using byte = std::uint8_t;
using sbyte = std::int8_t;
using ushort = std::uint16_t;
using uint = std::uint32_t;
using ulong = std::uint64_t;

//using long = std::int64_t //Sadly we cannot do this.

// nameof, commonly used in iced.
#define nameof(x) #x
