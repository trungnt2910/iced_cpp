﻿// C# helper headers
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

#include "Iced.Intel.IcedConstants.h"

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	namespace MemorySizeExtensionsPrivate_
	{
		inline static constexpr std::array<MemorySizeInfo, IcedConstants::MemorySizeEnumCount> GetMemorySizeInfos()
		{
			constexpr std::array data = std::to_array<std::uint8_t>({ 0x00, 0x00, 0x00, 0x01, 0x21, 0x00, 0x02, 0x42, 0x00, 0x03, 0x63, 0x00, 0x04, 0xA5, 0x00, 0x05, 0xA5, 0x00, 0x06, 0x08, 0x01, 0x07, 0x4A, 0x01, 0x08, 0x8C, 0x01, 0x09, 0x21, 0x80, 0x0A, 0x42, 0x80, 0x0B, 0x63, 0x80, 0x0C, 0xA5, 0x80, 0x0D, 0x08, 0x81, 0x0E, 0x4A, 0x81, 0x0F, 0x8C, 0x81, 0x10, 0x63, 0x00, 0x11, 0x84, 0x00, 0x12, 0xC6, 0x00, 0x13, 0x42, 0x00, 0x14, 0x63, 0x00, 0x15, 0xA5, 0x00, 0x02, 0x43, 0x00, 0x03, 0x65, 0x00, 0x18, 0xA5, 0x00, 0x19, 0x08, 0x01, 0x1A, 0x84, 0x00, 0x1B, 0xC6, 0x00, 0x1C, 0x42, 0x80, 0x1D, 0x63, 0x80, 0x1E, 0xA5, 0x80, 0x1F, 0xC6, 0x80, 0x20, 0x08, 0x81, 0x21, 0x42, 0x80, 0x22, 0xE7, 0x00, 0x23, 0x29, 0x01, 0x24, 0xAD, 0x01, 0x25, 0xCE, 0x01, 0x26, 0xEF, 0x01, 0x27, 0xEF, 0x01, 0x28, 0x00, 0x00, 0x29, 0x00, 0x00, 0x2A, 0xC6, 0x80, 0x2B, 0x8C, 0x01, 0x2C, 0x00, 0x00, 0x2D, 0xC6, 0x00, 0x2E, 0x6B, 0x01, 0x2F, 0x8C, 0x01, 0x01, 0x22, 0x00, 0x09, 0x22, 0x80, 0x01, 0x23, 0x00, 0x09, 0x23, 0x80, 0x02, 0x43, 0x00, 0x0A, 0x43, 0x80, 0x1C, 0x43, 0x80, 0x21, 0x43, 0x80, 0x01, 0x25, 0x00, 0x09, 0x25, 0x80, 0x02, 0x45, 0x00, 0x0A, 0x45, 0x80, 0x03, 0x65, 0x00, 0x0B, 0x65, 0x80, 0x1C, 0x45, 0x80, 0x1D, 0x65, 0x80, 0x01, 0x28, 0x00, 0x09, 0x28, 0x80, 0x02, 0x48, 0x00, 0x0A, 0x48, 0x80, 0x03, 0x68, 0x00, 0x0B, 0x68, 0x80, 0x04, 0xA8, 0x00, 0x05, 0xA8, 0x00, 0x0C, 0xA8, 0x80, 0x1C, 0x48, 0x80, 0x1D, 0x68, 0x80, 0x1E, 0xA8, 0x80, 0x36, 0x68, 0x80, 0x37, 0x68, 0x80, 0x01, 0x2A, 0x00, 0x09, 0x2A, 0x80, 0x02, 0x4A, 0x00, 0x0A, 0x4A, 0x80, 0x03, 0x6A, 0x00, 0x0B, 0x6A, 0x80, 0x04, 0xAA, 0x00, 0x05, 0xAA, 0x00, 0x0C, 0xAA, 0x80, 0x06, 0x0A, 0x01, 0x0D, 0x0A, 0x81, 0x1C, 0x4A, 0x80, 0x1D, 0x6A, 0x80, 0x1E, 0xAA, 0x80, 0x20, 0x0A, 0x81, 0x36, 0x6A, 0x80, 0x37, 0x6A, 0x80, 0x01, 0x2C, 0x00, 0x09, 0x2C, 0x80, 0x02, 0x4C, 0x00, 0x0A, 0x4C, 0x80, 0x03, 0x6C, 0x00, 0x0B, 0x6C, 0x80, 0x04, 0xAC, 0x00, 0x05, 0xAC, 0x00, 0x0C, 0xAC, 0x80, 0x06, 0x0C, 0x01, 0x1C, 0x4C, 0x80, 0x1D, 0x6C, 0x80, 0x1E, 0xAC, 0x80, 0x36, 0x6C, 0x80, 0x37, 0x6C, 0x80, 0x1C, 0x42, 0x80, 0x03, 0x63, 0x00, 0x0B, 0x63, 0x80, 0x1C, 0x42, 0x80, 0x1D, 0x63, 0x80, 0x0A, 0x42, 0x00, 0x02, 0x42, 0x00, 0x03, 0x63, 0x00, 0x0B, 0x63, 0x80, 0x04, 0xA5, 0x00, 0x05, 0xA5, 0x00, 0x0C, 0xA5, 0x80, 0x1C, 0x42, 0x80, 0x1D, 0x63, 0x80, 0x1E, 0xA5, 0x80, 0x35, 0x63, 0x80, 0x3D, 0xA5, 0x80, 0x3C, 0xA5, 0x00, 0x36, 0x63, 0x80, 0x37, 0x63, 0x80, 0x0A, 0x42, 0x00, 0x02, 0x42, 0x00, 0x03, 0x63, 0x00, 0x0B, 0x63, 0x80, 0x04, 0xA5, 0x00, 0x05, 0xA5, 0x00, 0x0C, 0xA5, 0x80, 0x1C, 0x42, 0x80, 0x1D, 0x63, 0x80, 0x1E, 0xA5, 0x80, 0x35, 0x63, 0x80, 0x3D, 0xA5, 0x80, 0x3C, 0xA5, 0x00, 0x36, 0x63, 0x80, 0x37, 0x63, 0x80, 0x0A, 0x42, 0x00, 0x02, 0x42, 0x00, 0x03, 0x63, 0x00, 0x0B, 0x63, 0x80, 0x04, 0xA5, 0x00, 0x05, 0xA5, 0x00, 0x0C, 0xA5, 0x80, 0x1C, 0x42, 0x80, 0x1D, 0x63, 0x80, 0x1E, 0xA5, 0x80, 0x36, 0x63, 0x80, 0x35, 0x63, 0x80, 0x3C, 0xA5, 0x00, 0x3D, 0xA5, 0x80, 0x37, 0x63, 0x80 });
			// GENERATOR-BEGIN: ConstData
			// ⚠️This was generated by GENERATOR!🦹‍♂️
			constexpr std::uint16_t IsSigned = 32768;
			constexpr std::uint32_t SizeMask = 31;
			constexpr std::int32_t SizeShift = 0;
			constexpr std::int32_t ElemSizeShift = 5;
			constexpr std::array sizes = std::to_array<std::uint16_t>({ 0, 1, 2, 4, 6, 8, 10, 14, 16, 28, 32, 48, 64, 94, 108, 512 });
			// GENERATOR-END: ConstData
			std::array<MemorySizeInfo, IcedConstants::MemorySizeEnumCount> infos;
			for (std::int32_t i = 0, j = 0; i < infos.size(); i++, j += 3)
			{
				auto elementType = static_cast<MemorySize>(data[j]);
				std::uint32_t value = static_cast<std::uint32_t>(data[j + 2] << 8) | data[j + 1];
				auto size = sizes[static_cast<std::int32_t>((value >> SizeShift) & SizeMask)];
				auto elementSize = sizes[static_cast<std::int32_t>((value >> ElemSizeShift) & SizeMask)];
				infos[i] = MemorySizeInfo(static_cast<MemorySize>(i), size, elementSize, elementType, (value & IsSigned) != 0, i >= static_cast<std::int32_t>(IcedConstants::FirstBroadcastMemorySize));
			}

			return infos;
		}
	}

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
		constexpr static bool IsBroadcast(MemorySize memorySize);

		static constexpr std::array<MemorySizeInfo, IcedConstants::MemorySizeEnumCount> MemorySizeInfos = MemorySizeExtensionsPrivate_::GetMemorySizeInfos();
		/// <summary>
		/// Gets the memory size info
		/// </summary>
		/// <param name="memorySize">Memory size</param>
		/// <returns></returns>
	public:
		constexpr static MemorySizeInfo GetInfo(MemorySize memorySize);
		/// <summary>
		/// Gets the size in bytes of the memory location or 0 if it's not accessed by the instruction or unknown or variable sized
		/// </summary>
		/// <param name="memorySize">Memory size</param>
		/// <returns></returns>
		constexpr static std::int32_t GetSize(MemorySize memorySize);
		/// <summary>
		/// Gets the size in bytes of the packed element. If it's not a packed data type, it's equal to <see cref="GetSize(MemorySize)"/>.
		/// </summary>
		/// <param name="memorySize">Memory size</param>
		/// <returns></returns>
		constexpr static std::int32_t GetElementSize(MemorySize memorySize);
		/// <summary>
		/// Gets the element type if it's packed data or <paramref name="memorySize"/> if it's not packed data
		/// </summary>
		/// <param name="memorySize">Memory size</param>
		/// <returns></returns>
		constexpr static MemorySize GetElementType(MemorySize memorySize);
		/// <summary>
		/// Gets the element type info if it's packed data or <paramref name="memorySize"/> if it's not packed data
		/// </summary>
		/// <param name="memorySize">Memory size</param>
		/// <returns></returns>
		constexpr static MemorySizeInfo GetElementTypeInfo(MemorySize memorySize);
		/// <summary>
		/// <see langword="true"/> if it's signed data (signed integer or a floating point value)
		/// </summary>
		/// <param name="memorySize">Memory size</param>
		/// <returns></returns>
		constexpr static bool IsSigned(MemorySize memorySize);
		/// <summary>
		/// <see langword="true"/> if this is a packed data type, eg. <see cref="MemorySize.Packed128_Float32"/>
		/// </summary>
		/// <param name="memorySize">Memory size</param>
		/// <returns></returns>
		constexpr static bool IsPacked(MemorySize memorySize);
		/// <summary>
		/// Gets the number of elements in the packed data type or 1 if it's not packed data (<see cref="IsPacked"/>)
		/// </summary>
		/// <param name="memorySize">Memory size</param>
		/// <returns></returns>
		constexpr static std::int32_t GetElementCount(MemorySize memorySize);
	};


	constexpr bool MemorySizeExtensions::IsBroadcast(MemorySize memorySize)
	{
		return memorySize >= IcedConstants::FirstBroadcastMemorySize;
	}

	constexpr MemorySizeInfo MemorySizeExtensions::GetInfo(MemorySize memorySize)
	{
		const auto& infos = MemorySizeInfos;
		if (static_cast<std::uint32_t>(memorySize) >= static_cast<std::uint32_t>(infos.size()))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_memorySize();
		}
		return infos[static_cast<std::int32_t>(memorySize)];
	}

	constexpr std::int32_t MemorySizeExtensions::GetSize(MemorySize memorySize)
	{
		return Iced::Intel::MemorySizeExtensions::GetInfo(memorySize).GetSize();
	}

	constexpr std::int32_t MemorySizeExtensions::GetElementSize(MemorySize memorySize)
	{
		return Iced::Intel::MemorySizeExtensions::GetInfo(memorySize).GetElementSize();
	}

	constexpr MemorySize MemorySizeExtensions::GetElementType(MemorySize memorySize)
	{
		return Iced::Intel::MemorySizeExtensions::GetInfo(memorySize).GetElementType();
	}

	constexpr MemorySizeInfo MemorySizeExtensions::GetElementTypeInfo(MemorySize memorySize)
	{
		return Iced::Intel::MemorySizeExtensions::GetInfo(Iced::Intel::MemorySizeExtensions::GetInfo(memorySize).GetElementType());
	}

	constexpr bool MemorySizeExtensions::IsSigned(MemorySize memorySize)
	{
		return Iced::Intel::MemorySizeExtensions::GetInfo(memorySize).IsSigned();
	}

	constexpr bool MemorySizeExtensions::IsPacked(MemorySize memorySize)
	{
		return Iced::Intel::MemorySizeExtensions::GetInfo(memorySize).IsPacked();
	}

	constexpr std::int32_t MemorySizeExtensions::GetElementCount(MemorySize memorySize)
	{
		return Iced::Intel::MemorySizeExtensions::GetInfo(memorySize).GetElementCount();
	}
}
