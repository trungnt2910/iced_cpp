// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

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
		constexpr Register GetSegment() const;
		/// <summary>
		/// Base register or <see cref="Register.None"/> if none
		/// </summary>
		constexpr Register GetBase() const;
		/// <summary>
		/// Index register or <see cref="Register.None"/> if none
		/// </summary>
		constexpr Register GetIndex() const;
		/// <summary>
		/// Index scale (1, 2, 4 or 8)
		/// </summary>
		constexpr std::int32_t GetScale() const;
		/// <summary>
		/// Displacement
		/// </summary>
		constexpr std::uint64_t GetDisplacement() const;
		/// <summary>
		/// Size of location
		/// </summary>
		constexpr Iced::Intel::MemorySize GetMemorySize() const;
		/// <summary>
		/// Memory access
		/// </summary>
		constexpr OpAccess GetAccess() const;
		/// <summary>
		/// Address size
		/// </summary>
		constexpr CodeSize GetAddressSize() const;
		/// <summary>
		/// VSIB size (<c>0</c>, <c>4</c> or <c>8</c>)
		/// </summary>
		constexpr std::int32_t GetVsibSize() const;
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
		constexpr UsedMemory(Register segReg, Register baseReg, Register indexReg, std::int32_t scale, std::int64_t displ, Iced::Intel::MemorySize memorySize, OpAccess access);
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
		constexpr UsedMemory(Register segReg, Register baseReg, Register indexReg, std::int32_t scale, std::uint64_t displ, Iced::Intel::MemorySize memorySize, OpAccess access);
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
		constexpr UsedMemory(Register segReg, Register baseReg, Register indexReg, std::int32_t scale, std::int64_t displ, Iced::Intel::MemorySize memorySize, OpAccess access, CodeSize addressSize, std::int32_t vsibSize);
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
		constexpr UsedMemory(Register segReg, Register baseReg, Register indexReg, std::int32_t scale, std::uint64_t displ, Iced::Intel::MemorySize memorySize, OpAccess access, CodeSize addressSize, std::int32_t vsibSize);
		/// <summary>
		/// Gets the virtual address of a memory operand
		/// </summary>
		/// <param name="elementIndex">Only used if it's a vsib memory operand. This is the element index of the vector index register.</param>
		/// <param name="getRegisterValue">Delegate that returns the value of a register or the base address of a segment register</param>
		/// <returns></returns>
		std::uint64_t GetVirtualAddress(std::int32_t elementIndex, VAGetRegisterValue getRegisterValue) const;
		/// <summary>
		/// Gets the virtual address of a memory operand
		/// </summary>
		/// <param name="elementIndex">Only used if it's a vsib memory operand. This is the element index of the vector index register.</param>
		/// <param name="registerValueProvider">Returns values of registers and segment base addresses</param>
		/// <returns></returns>
		std::uint64_t GetVirtualAddress(std::int32_t elementIndex, IVARegisterValueProvider* registerValueProvider) const;
		/// <summary>
		/// Gets the virtual address of a memory operand
		/// </summary>
		/// <param name="elementIndex">Only used if it's a vsib memory operand. This is the element index of the vector index register.</param>
		/// <param name="result">Result if this method returns <see langword="true"/></param>
		/// <param name="getRegisterValue">Returns values of registers and segment base addresses</param>
		/// <returns></returns>
		bool TryGetVirtualAddress(std::int32_t elementIndex, std::uint64_t& result, VATryGetRegisterValue getRegisterValue) const;
		/// <summary>
		/// Gets the virtual address of a memory operand
		/// </summary>
		/// <param name="elementIndex">Only used if it's a vsib memory operand. This is the element index of the vector index register.</param>
		/// <param name="registerValueProvider">Returns values of registers and segment base addresses</param>
		/// <param name="result">Result if this method returns <see langword="true"/></param>
		/// <returns></returns>
		bool TryGetVirtualAddress(std::int32_t elementIndex, IVATryGetRegisterValueProvider* registerValueProvider, std::uint64_t& result) const;
		/// <summary>
		/// ToString()
		/// </summary>
		/// <returns></returns>
		constexpr std::string ToString() const;

		constexpr UsedMemory() = default;
	};

	constexpr Register UsedMemory::GetSegment() const
	{
		return static_cast<Register>(segReg);
	}

	constexpr Register UsedMemory::GetBase() const
	{
		return static_cast<Register>(baseReg);
	}

	constexpr Register UsedMemory::GetIndex() const
	{
		return static_cast<Register>(indexReg);
	}

	constexpr std::int32_t UsedMemory::GetScale() const
	{
		return scale;
	}

	constexpr std::uint64_t UsedMemory::GetDisplacement() const
	{
		return displ;
	}

	constexpr Iced::Intel::MemorySize UsedMemory::GetMemorySize() const
	{
		return static_cast<Iced::Intel::MemorySize>(memorySize);
	}

	constexpr OpAccess UsedMemory::GetAccess() const
	{
		return static_cast<OpAccess>(access);
	}

	constexpr CodeSize UsedMemory::GetAddressSize() const
	{
		return static_cast<CodeSize>(addressSize);
	}

	constexpr std::int32_t UsedMemory::GetVsibSize() const
	{
		return vsibSize;
	}

	constexpr UsedMemory::UsedMemory(Register segReg, Register baseReg, Register indexReg, std::int32_t scale, std::int64_t displ, Iced::Intel::MemorySize memorySize, OpAccess access)
	{
		this->displ = static_cast<std::uint64_t>(displ);
		assert(static_cast<std::uint32_t>(segReg) <= std::numeric_limits<std::uint8_t>::max());
		this->segReg = static_cast<std::uint8_t>(segReg);
		assert(static_cast<std::uint32_t>(baseReg) <= std::numeric_limits<std::uint8_t>::max());
		this->baseReg = static_cast<std::uint8_t>(baseReg);
		assert(static_cast<std::uint32_t>(indexReg) <= std::numeric_limits<std::uint8_t>::max());
		this->indexReg = static_cast<std::uint8_t>(indexReg);
		assert(static_cast<std::uint32_t>(memorySize) <= std::numeric_limits<std::uint8_t>::max());
		this->memorySize = static_cast<std::uint8_t>(memorySize);
		assert(scale == 1 || scale == 2 || scale == 4 || scale == 8);
		this->scale = static_cast<std::uint8_t>(scale);
		assert(static_cast<std::uint32_t>(access) <= std::numeric_limits<std::uint8_t>::max());
		this->access = static_cast<std::uint8_t>(access);
		addressSize = static_cast<std::uint8_t>(CodeSize::Unknown);
		vsibSize = 0;
	}

	constexpr UsedMemory::UsedMemory(Register segReg, Register baseReg, Register indexReg, std::int32_t scale, std::uint64_t displ, Iced::Intel::MemorySize memorySize, OpAccess access)
	{
		this->displ = displ;
		assert(static_cast<std::uint32_t>(segReg) <= std::numeric_limits<std::uint8_t>::max());
		this->segReg = static_cast<std::uint8_t>(segReg);
		assert(static_cast<std::uint32_t>(baseReg) <= std::numeric_limits<std::uint8_t>::max());
		this->baseReg = static_cast<std::uint8_t>(baseReg);
		assert(static_cast<std::uint32_t>(indexReg) <= std::numeric_limits<std::uint8_t>::max());
		this->indexReg = static_cast<std::uint8_t>(indexReg);
		assert(static_cast<std::uint32_t>(memorySize) <= std::numeric_limits<std::uint8_t>::max());
		this->memorySize = static_cast<std::uint8_t>(memorySize);
		assert(scale == 1 || scale == 2 || scale == 4 || scale == 8);
		this->scale = static_cast<std::uint8_t>(scale);
		assert(static_cast<std::uint32_t>(access) <= std::numeric_limits<std::uint8_t>::max());
		this->access = static_cast<std::uint8_t>(access);
		addressSize = static_cast<std::uint8_t>(CodeSize::Unknown);
		vsibSize = 0;
	}

	constexpr UsedMemory::UsedMemory(Register segReg, Register baseReg, Register indexReg, std::int32_t scale, std::int64_t displ, Iced::Intel::MemorySize memorySize, OpAccess access, CodeSize addressSize, std::int32_t vsibSize)
	{
		this->displ = static_cast<std::uint64_t>(displ);
		assert(static_cast<std::uint32_t>(segReg) <= std::numeric_limits<std::uint8_t>::max());
		this->segReg = static_cast<std::uint8_t>(segReg);
		assert(static_cast<std::uint32_t>(baseReg) <= std::numeric_limits<std::uint8_t>::max());
		this->baseReg = static_cast<std::uint8_t>(baseReg);
		assert(static_cast<std::uint32_t>(indexReg) <= std::numeric_limits<std::uint8_t>::max());
		this->indexReg = static_cast<std::uint8_t>(indexReg);
		assert(static_cast<std::uint32_t>(memorySize) <= std::numeric_limits<std::uint8_t>::max());
		this->memorySize = static_cast<std::uint8_t>(memorySize);
		assert(scale == 1 || scale == 2 || scale == 4 || scale == 8);
		this->scale = static_cast<std::uint8_t>(scale);
		assert(static_cast<std::uint32_t>(access) <= std::numeric_limits<std::uint8_t>::max());
		this->access = static_cast<std::uint8_t>(access);
		assert(static_cast<std::uint32_t>(addressSize) <= std::numeric_limits<std::uint8_t>::max());
		this->addressSize = static_cast<std::uint8_t>(addressSize);
		assert(vsibSize == 0 || vsibSize == 4 || vsibSize == 8);
		this->vsibSize = static_cast<std::uint8_t>(vsibSize);
	}

	constexpr UsedMemory::UsedMemory(Register segReg, Register baseReg, Register indexReg, std::int32_t scale, std::uint64_t displ, Iced::Intel::MemorySize memorySize, OpAccess access, CodeSize addressSize, std::int32_t vsibSize)
	{
		this->displ = displ;
		assert(static_cast<std::uint32_t>(segReg) <= std::numeric_limits<std::uint8_t>::max());
		this->segReg = static_cast<std::uint8_t>(segReg);
		assert(static_cast<std::uint32_t>(baseReg) <= std::numeric_limits<std::uint8_t>::max());
		this->baseReg = static_cast<std::uint8_t>(baseReg);
		assert(static_cast<std::uint32_t>(indexReg) <= std::numeric_limits<std::uint8_t>::max());
		this->indexReg = static_cast<std::uint8_t>(indexReg);
		assert(static_cast<std::uint32_t>(memorySize) <= std::numeric_limits<std::uint8_t>::max());
		this->memorySize = static_cast<std::uint8_t>(memorySize);
		assert(scale == 1 || scale == 2 || scale == 4 || scale == 8);
		this->scale = static_cast<std::uint8_t>(scale);
		assert(static_cast<std::uint32_t>(access) <= std::numeric_limits<std::uint8_t>::max());
		this->access = static_cast<std::uint8_t>(access);
		assert(static_cast<std::uint32_t>(addressSize) <= std::numeric_limits<std::uint8_t>::max());
		this->addressSize = static_cast<std::uint8_t>(addressSize);
		assert(vsibSize == 0 || vsibSize == 4 || vsibSize == 8);
		this->vsibSize = static_cast<std::uint8_t>(vsibSize);
	}

	constexpr std::string UsedMemory::ToString() const
	{
		std::string sb;
		sb.push_back('[');
		//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
		sb.append(to_string(GetSegment()));
		sb.push_back(':');
		bool needPlus = false;
		if (GetBase() != Register::None)
		{
			//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
			sb.append(to_string(GetBase()));
			needPlus = true;
		}
		if (GetIndex() != Register::None)
		{
			if (needPlus)
			{
				sb.push_back('+');
			}
			needPlus = true;
			//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
			sb.append(to_string(GetIndex()));
			if (GetScale() != 1)
			{
				sb.push_back('*');
				sb.push_back(static_cast<char>('0' + GetScale()));
			}
		}
		if (GetDisplacement() != 0 || !needPlus)
		{
			if (needPlus)
			{
				sb.push_back('+');
			}
			if (GetDisplacement() <= 9)
			{
				sb.append(std::to_string(GetDisplacement()));
			}
			else
			{
				sb.append("0x");
				sb.append(std::format("{:X}", GetDisplacement()));
			}
		}
		sb.push_back(';');
		sb.append(to_string(GetMemorySize()));
		sb.push_back(';');
		sb.append(to_string(GetAccess()));
		sb.push_back(']');
		return sb;
	}
}
