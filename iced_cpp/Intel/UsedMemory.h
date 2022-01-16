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
#include "MemorySize.g.h"
#include "OpAccess.g.h"
#include "CodeSize.g.h"
#include "Instruction.VA.h"
#include <string>
#include <limits>
#include <stdexcept>
#include <cassert>
#include <csharp/stringbuilder.h>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// A memory location used by an instruction
	/// </summary>
	class UsedMemory
	{
		/* readonly */
	private:
		std::uint64_t displ = 0;
		/* readonly */
		std::uint8_t segReg = 0;
		/* readonly */
		std::uint8_t baseReg = 0;
		/* readonly */
		std::uint8_t indexReg = 0;
		/* readonly */
		std::uint8_t memorySize = 0;
		/* readonly */
		std::uint8_t scale = 0;
		/* readonly */
		std::uint8_t access = 0;
		/* readonly */
		std::uint8_t addressSize = 0;
		/* readonly */
		std::uint8_t vsibSize = 0;
		/// <summary>
		/// Effective segment register or <see cref="Register.None"/> if the segment register is ignored
		/// </summary>
	public:
		Register GetSegment() const;
		/// <summary>
		/// Base register or <see cref="Register.None"/> if none
		/// </summary>
		Register GetBase() const;
		/// <summary>
		/// Index register or <see cref="Register.None"/> if none
		/// </summary>
		Register GetIndex() const;
		/// <summary>
		/// Index scale (1, 2, 4 or 8)
		/// </summary>
		std::int32_t GetScale() const;
		/// <summary>
		/// Displacement
		/// </summary>
		std::uint64_t GetDisplacement() const;
		/// <summary>
		/// Size of location
		/// </summary>
		Iced::Intel::MemorySize GetMemorySize() const;
		/// <summary>
		/// Memory access
		/// </summary>
		OpAccess GetAccess() const;
		/// <summary>
		/// Address size
		/// </summary>
		CodeSize GetAddressSize() const;
		/// <summary>
		/// VSIB size (<c>0</c>, <c>4</c> or <c>8</c>)
		/// </summary>
		std::int32_t GetVsibSize() const;
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="segReg">Effective segment register or <see cref="Register.None"/> if the segment register is ignored</param>
		/// <param name="baseReg">Base register</param>
		/// <param name="indexReg">Index register</param>
		/// <param name="scale">1, 2, 4 or 8</param>
		/// <param name="displ">Displacement</param>
		/// <param name="memorySize">Memory size</param>
		/// <param name="access">Access</param>
		UsedMemory(Register segReg, Register baseReg, Register indexReg, std::int32_t scale, std::int64_t displ, Iced::Intel::MemorySize memorySize, OpAccess access);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="segReg">Effective segment register or <see cref="Register.None"/> if the segment register is ignored</param>
		/// <param name="baseReg">Base register</param>
		/// <param name="indexReg">Index register</param>
		/// <param name="scale">1, 2, 4 or 8</param>
		/// <param name="displ">Displacement</param>
		/// <param name="memorySize">Memory size</param>
		/// <param name="access">Access</param>
		UsedMemory(Register segReg, Register baseReg, Register indexReg, std::int32_t scale, std::uint64_t displ, Iced::Intel::MemorySize memorySize, OpAccess access);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="segReg">Effective segment register or <see cref="Register.None"/> if the segment register is ignored</param>
		/// <param name="baseReg">Base register</param>
		/// <param name="indexReg">Index register</param>
		/// <param name="scale">1, 2, 4 or 8</param>
		/// <param name="displ">Displacement</param>
		/// <param name="memorySize">Memory size</param>
		/// <param name="access">Access</param>
		/// <param name="addressSize">Address size</param>
		/// <param name="vsibSize">VSIB size (<c>0</c>, <c>4</c> or <c>8</c>)</param>
		UsedMemory(Register segReg, Register baseReg, Register indexReg, std::int32_t scale, std::int64_t displ, Iced::Intel::MemorySize memorySize, OpAccess access, CodeSize addressSize, std::int32_t vsibSize);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="segReg">Effective segment register or <see cref="Register.None"/> if the segment register is ignored</param>
		/// <param name="baseReg">Base register</param>
		/// <param name="indexReg">Index register</param>
		/// <param name="scale">1, 2, 4 or 8</param>
		/// <param name="displ">Displacement</param>
		/// <param name="memorySize">Memory size</param>
		/// <param name="access">Access</param>
		/// <param name="addressSize">Address size</param>
		/// <param name="vsibSize">VSIB size (<c>0</c>, <c>4</c> or <c>8</c>)</param>
		UsedMemory(Register segReg, Register baseReg, Register indexReg, std::int32_t scale, std::uint64_t displ, Iced::Intel::MemorySize memorySize, OpAccess access, CodeSize addressSize, std::int32_t vsibSize);
		/// <summary>
		/// Gets the virtual address of a memory operand
		/// </summary>
		/// <param name="elementIndex">Only used if it's a vsib memory operand. This is the element index of the vector index register.</param>
		/// <param name="getRegisterValue">Delegate that returns the value of a register or the base address of a segment register</param>
		/// <returns></returns>
		std::uint64_t GetVirtualAddress(std::int32_t elementIndex, VAGetRegisterValue getRegisterValue);
		/// <summary>
		/// Gets the virtual address of a memory operand
		/// </summary>
		/// <param name="elementIndex">Only used if it's a vsib memory operand. This is the element index of the vector index register.</param>
		/// <param name="registerValueProvider">Returns values of registers and segment base addresses</param>
		/// <returns></returns>
		std::uint64_t GetVirtualAddress(std::int32_t elementIndex, IVARegisterValueProvider* registerValueProvider);
		/// <summary>
		/// Gets the virtual address of a memory operand
		/// </summary>
		/// <param name="elementIndex">Only used if it's a vsib memory operand. This is the element index of the vector index register.</param>
		/// <param name="result">Result if this method returns <see langword="true"/></param>
		/// <param name="getRegisterValue">Returns values of registers and segment base addresses</param>
		/// <returns></returns>
		bool TryGetVirtualAddress(std::int32_t elementIndex, std::uint64_t& result, VATryGetRegisterValue getRegisterValue);
		/// <summary>
		/// Gets the virtual address of a memory operand
		/// </summary>
		/// <param name="elementIndex">Only used if it's a vsib memory operand. This is the element index of the vector index register.</param>
		/// <param name="registerValueProvider">Returns values of registers and segment base addresses</param>
		/// <param name="result">Result if this method returns <see langword="true"/></param>
		/// <returns></returns>
		bool TryGetVirtualAddress(std::int32_t elementIndex, IVATryGetRegisterValueProvider* registerValueProvider, std::uint64_t& result);
		/// <summary>
		/// ToString()
		/// </summary>
		/// <returns></returns>
		std::string ToString();

		UsedMemory() = default;
	};
}
