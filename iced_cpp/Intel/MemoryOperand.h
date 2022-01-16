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

#include "Register.g.h"

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// Memory operand
	/// </summary>
	class MemoryOperand
	{
		/// <summary>
		/// Segment override or <see cref="Register.None"/>
		/// </summary>
	public:
		Register SegmentPrefix = static_cast<Register>(0);
		/// <summary>
		/// Base register or <see cref="Register.None"/>
		/// </summary>
		Register Base = static_cast<Register>(0);
		/// <summary>
		/// Index register or <see cref="Register.None"/>
		/// </summary>
		Register Index = static_cast<Register>(0);
		/// <summary>
		/// Index register scale (1, 2, 4, or 8)
		/// </summary>
		std::int32_t Scale = 0;
		/// <summary>
		/// Memory displacement
		/// </summary>
		std::int64_t Displacement = 0;
		/// <summary>
		/// 0 (no displ), 1 (16/32/64-bit, but use 2/4/8 if it doesn't fit in a <see cref="sbyte"/>), 2 (16-bit), 4 (32-bit) or 8 (64-bit)
		/// </summary>
		std::int32_t DisplSize = 0;
		/// <summary>
		/// <see langword="true"/> if it's broadcast memory (EVEX instructions)
		/// </summary>
		bool IsBroadcast = false;
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="base">Base register or <see cref="Register.None"/></param>
		/// <param name="index">Index register or <see cref="Register.None"/></param>
		/// <param name="scale">Index register scale (1, 2, 4, or 8)</param>
		/// <param name="displacement">Memory displacement</param>
		/// <param name="displSize">0 (no displ), 1 (16/32/64-bit, but use 2/4/8 if it doesn't fit in a <see cref="sbyte"/>), 2 (16-bit), 4 (32-bit) or 8 (64-bit)</param>
		/// <param name="isBroadcast"><see langword="true"/> if it's broadcast memory (EVEX instructions)</param>
		/// <param name="segmentPrefix">Segment override or <see cref="Register.None"/></param>
		MemoryOperand(Register base, Register index, std::int32_t scale, std::int64_t displacement, std::int32_t displSize, bool isBroadcast, Register segmentPrefix);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="base">Base register or <see cref="Register.None"/></param>
		/// <param name="index">Index register or <see cref="Register.None"/></param>
		/// <param name="scale">Index register scale (1, 2, 4, or 8)</param>
		/// <param name="isBroadcast"><see langword="true"/> if it's broadcast memory (EVEX instructions)</param>
		/// <param name="segmentPrefix">Segment override or <see cref="Register.None"/></param>
		MemoryOperand(Register base, Register index, std::int32_t scale, bool isBroadcast, Register segmentPrefix);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="base">Base register or <see cref="Register.None"/></param>
		/// <param name="displacement">Memory displacement</param>
		/// <param name="displSize">0 (no displ), 1 (16/32/64-bit, but use 2/4/8 if it doesn't fit in a <see cref="sbyte"/>), 2 (16-bit), 4 (32-bit) or 8 (64-bit)</param>
		/// <param name="isBroadcast"><see langword="true"/> if it's broadcast memory (EVEX instructions)</param>
		/// <param name="segmentPrefix">Segment override or <see cref="Register.None"/></param>
		MemoryOperand(Register base, std::int64_t displacement, std::int32_t displSize, bool isBroadcast, Register segmentPrefix);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="index">Index register or <see cref="Register.None"/></param>
		/// <param name="scale">Index register scale (1, 2, 4, or 8)</param>
		/// <param name="displacement">Memory displacement</param>
		/// <param name="displSize">0 (no displ), 1 (16/32/64-bit, but use 2/4/8 if it doesn't fit in a <see cref="sbyte"/>), 2 (16-bit), 4 (32-bit) or 8 (64-bit)</param>
		/// <param name="isBroadcast"><see langword="true"/> if it's broadcast memory (EVEX instructions)</param>
		/// <param name="segmentPrefix">Segment override or <see cref="Register.None"/></param>
		MemoryOperand(Register index, std::int32_t scale, std::int64_t displacement, std::int32_t displSize, bool isBroadcast, Register segmentPrefix);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="base">Base register or <see cref="Register.None"/></param>
		/// <param name="displacement">Memory displacement</param>
		/// <param name="isBroadcast"><see langword="true"/> if it's broadcast memory (EVEX instructions)</param>
		/// <param name="segmentPrefix">Segment override or <see cref="Register.None"/></param>
		MemoryOperand(Register base, std::int64_t displacement, bool isBroadcast, Register segmentPrefix);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="base">Base register or <see cref="Register.None"/></param>
		/// <param name="index">Index register or <see cref="Register.None"/></param>
		/// <param name="scale">Index register scale (1, 2, 4, or 8)</param>
		/// <param name="displacement">Memory displacement</param>
		/// <param name="displSize">0 (no displ), 1 (16/32/64-bit, but use 2/4/8 if it doesn't fit in a <see cref="sbyte"/>), 2 (16-bit), 4 (32-bit) or 8 (64-bit)</param>
		MemoryOperand(Register base, Register index, std::int32_t scale, std::int64_t displacement, std::int32_t displSize);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="base">Base register or <see cref="Register.None"/></param>
		/// <param name="index">Index register or <see cref="Register.None"/></param>
		/// <param name="scale">Index register scale (1, 2, 4, or 8)</param>
		MemoryOperand(Register base, Register index, std::int32_t scale);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="base">Base register or <see cref="Register.None"/></param>
		/// <param name="index">Index register or <see cref="Register.None"/></param>
		MemoryOperand(Register base, Register index);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="base">Base register or <see cref="Register.None"/></param>
		/// <param name="displacement">Memory displacement</param>
		/// <param name="displSize">0 (no displ), 1 (16/32/64-bit, but use 2/4/8 if it doesn't fit in a <see cref="sbyte"/>), 2 (16-bit), 4 (32-bit) or 8 (64-bit)</param>
		MemoryOperand(Register base, std::int64_t displacement, std::int32_t displSize);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="index">Index register or <see cref="Register.None"/></param>
		/// <param name="scale">Index register scale (1, 2, 4, or 8)</param>
		/// <param name="displacement">Memory displacement</param>
		/// <param name="displSize">0 (no displ), 1 (16/32/64-bit, but use 2/4/8 if it doesn't fit in a <see cref="sbyte"/>), 2 (16-bit), 4 (32-bit) or 8 (64-bit)</param>
		MemoryOperand(Register index, std::int32_t scale, std::int64_t displacement, std::int32_t displSize);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="base">Base register or <see cref="Register.None"/></param>
		/// <param name="displacement">Memory displacement</param>
		MemoryOperand(Register base, std::int64_t displacement);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="base">Base register or <see cref="Register.None"/></param>
		MemoryOperand(Register base);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="displacement">Memory displacement</param>
		/// <param name="displSize">0 (no displ), 1 (16/32/64-bit, but use 2/4/8 if it doesn't fit in a <see cref="sbyte"/>), 2 (16-bit), 4 (32-bit) or 8 (64-bit)</param>
		MemoryOperand(std::uint64_t displacement, std::int32_t displSize);

		MemoryOperand() = default;
	};
}
