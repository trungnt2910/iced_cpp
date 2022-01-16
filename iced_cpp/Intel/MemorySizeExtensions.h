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
#include <limits>
#include <cassert>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// <see cref="Intel.MemorySize"/> information
	/// </summary>
	class MemorySizeInfo
	{
		// 8 bytes in size
		/* readonly */
	private:
		std::uint16_t size = 0;
		/* readonly */
		std::uint16_t elementSize = 0;
		/* readonly */
		std::uint8_t memorySize = 0;
		/* readonly */
		std::uint8_t elementType = 0;
		// Use flags if more booleans are needed
		/* readonly */
		bool isSigned = false;
		/* readonly */
		bool isBroadcast = false;
		/// <summary>
		/// Gets the <see cref="Intel.MemorySize"/> value
		/// </summary>
	public:
		Iced::Intel::MemorySize GetMemorySize() const;
		/// <summary>
		/// Size in bytes of the memory location or 0 if it's not accessed or unknown
		/// </summary>
		std::int32_t GetSize() const;
		/// <summary>
		/// Size in bytes of the packed element. If it's not a packed data type, it's equal to <see cref="Size"/>.
		/// </summary>
		std::int32_t GetElementSize() const;
		/// <summary>
		/// Element type if it's packed data or the type itself if it's not packed data
		/// </summary>
		Iced::Intel::MemorySize GetElementType() const;
		/// <summary>
		/// <see langword="true"/> if it's signed data (signed integer or a floating point value)
		/// </summary>
		bool IsSigned() const;
		/// <summary>
		/// <see langword="true"/> if it's a broadcast memory type
		/// </summary>
		bool IsBroadcast() const;
		/// <summary>
		/// <see langword="true"/> if this is a packed data type, eg. <see cref="MemorySize.Packed128_Float32"/>. See also <see cref="ElementCount"/>
		/// </summary>
		bool IsPacked() const;
		/// <summary>
		/// Gets the number of elements in the packed data type or 1 if it's not packed data (<see cref="IsPacked"/>)
		/// </summary>
		std::int32_t GetElementCount() const;
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="memorySize">Memory size value</param>
		/// <param name="size">Size of location</param>
		/// <param name="elementSize">Size of the packed element, or <paramref name="size"/> if it's not packed data</param>
		/// <param name="elementType">Element type if it's packed data or <paramref name="memorySize"/> if it's not packed data</param>
		/// <param name="isSigned"><see langword="true"/> if signed data</param>
		/// <param name="isBroadcast"><see langword="true"/> if broadcast</param>
		MemorySizeInfo(Iced::Intel::MemorySize memorySize, std::int32_t size, std::int32_t elementSize, Iced::Intel::MemorySize elementType, bool isSigned, bool isBroadcast);

		MemorySizeInfo() = default;
	};
}
