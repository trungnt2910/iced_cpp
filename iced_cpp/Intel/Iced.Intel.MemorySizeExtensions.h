// C# helper headers
#include <csharp/classes.h>
#include <csharp/enum.h>
#include <csharp/interfaces.h>
#include <csharp/primitives.h>

// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#pragma once

#include "MemorySize.g.h"
#include "MemorySizeExtensions.h"
#include <vector>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// <see cref="MemorySize"/> extension methods
	/// </summary>
	class MemorySizeExtensions final
	{
		/// <summary>
		/// Checks if <paramref name="memorySize"/> is a broadcast memory type
		/// </summary>
		/// <param name="memorySize">Memory size</param>
		/// <returns></returns>
	public:
		static bool IsBroadcast(MemorySize memorySize);


		static std::vector<MemorySizeInfo> MemorySizeInfos;
	private:
		static std::vector<MemorySizeInfo> GetMemorySizeInfos();
		/// <summary>
		/// Gets the memory size info
		/// </summary>
		/// <param name="memorySize">Memory size</param>
		/// <returns></returns>
	public:
		static MemorySizeInfo GetInfo(MemorySize memorySize);
		/// <summary>
		/// Gets the size in bytes of the memory location or 0 if it's not accessed by the instruction or unknown or variable sized
		/// </summary>
		/// <param name="memorySize">Memory size</param>
		/// <returns></returns>
		static std::int32_t GetSize(MemorySize memorySize);
		/// <summary>
		/// Gets the size in bytes of the packed element. If it's not a packed data type, it's equal to <see cref="GetSize(MemorySize)"/>.
		/// </summary>
		/// <param name="memorySize">Memory size</param>
		/// <returns></returns>
		static std::int32_t GetElementSize(MemorySize memorySize);
		/// <summary>
		/// Gets the element type if it's packed data or <paramref name="memorySize"/> if it's not packed data
		/// </summary>
		/// <param name="memorySize">Memory size</param>
		/// <returns></returns>
		static MemorySize GetElementType(MemorySize memorySize);
		/// <summary>
		/// Gets the element type info if it's packed data or <paramref name="memorySize"/> if it's not packed data
		/// </summary>
		/// <param name="memorySize">Memory size</param>
		/// <returns></returns>
		static MemorySizeInfo GetElementTypeInfo(MemorySize memorySize);
		/// <summary>
		/// <see langword="true"/> if it's signed data (signed integer or a floating point value)
		/// </summary>
		/// <param name="memorySize">Memory size</param>
		/// <returns></returns>
		static bool IsSigned(MemorySize memorySize);
		/// <summary>
		/// <see langword="true"/> if this is a packed data type, eg. <see cref="MemorySize.Packed128_Float32"/>
		/// </summary>
		/// <param name="memorySize">Memory size</param>
		/// <returns></returns>
		static bool IsPacked(MemorySize memorySize);
		/// <summary>
		/// Gets the number of elements in the packed data type or 1 if it's not packed data (<see cref="IsPacked"/>)
		/// </summary>
		/// <param name="memorySize">Memory size</param>
		/// <returns></returns>
		static std::int32_t GetElementCount(MemorySize memorySize);
	};
}
