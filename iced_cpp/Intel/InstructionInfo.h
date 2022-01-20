// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include "UsedRegister.h"
#include "UsedMemory.h"
#include "OpAccess.g.h"
#include <vector>

#include "Iced.Intel.IcedConstants.h"
#include "InstructionInfoInternal/InfoHandlerFlags.h"

namespace Iced::Intel
{
	/// <summary>
	/// Contains information about an instruction, eg. read/written registers, read/written <c>RFLAGS</c> bits, <c>CPUID</c> feature bit, etc
	/// </summary>
	class InstructionInfo
	{
	private:
		std::vector<UsedRegister> usedRegisters;
		std::vector<UsedMemory> usedMemoryLocations;
		std::uint8_t opAccesses[IcedConstants::MaxOpCount];
		constexpr InstructionInfo(bool dummy);
		friend class InstructionInfoFactory;
	public:
		/// <summary>
		/// Gets a struct iterator that returns all accessed registers. This method doesn't return all accessed registers if <see cref="Instruction.IsSaveRestoreInstruction"/> is <see langword="true"/>.
		/// <br/>
		/// <br/>
		/// Some instructions have a <c>r16</c>/<c>r32</c> operand but only use the low 8 bits of the register. In that case
		/// this method returns the 8-bit register even if it's <c>SPL</c>, <c>BPL</c>, <c>SIL</c>, <c>DIL</c> and the
		/// instruction was decoded in 16 or 32-bit mode. This is more accurate than returning the <c>r16</c>/<c>r32</c>
		/// register. Example instructions that do this: <c>PINSRB</c>, <c>ARPL</c>
		/// </summary>
		/// <returns></returns>
		constexpr const std::vector<UsedRegister>& GetUsedRegisters() const;
		/// <summary>
		/// Gets a struct iterator that returns all accessed memory locations
		/// </summary>
		/// <returns></returns>
		constexpr const std::vector<UsedMemory>& GetUsedMemory() const;
		/// <summary>
		/// Operand #0 access
		/// </summary>
	public:
		constexpr OpAccess GetOp0Access() const;
		/// <summary>
		/// Operand #1 access
		/// </summary>
		constexpr OpAccess GetOp1Access() const;
		/// <summary>
		/// Operand #2 access
		/// </summary>
		constexpr OpAccess GetOp2Access() const;
		/// <summary>
		/// Operand #3 access
		/// </summary>
		constexpr OpAccess GetOp3Access() const;
		/// <summary>
		/// Operand #4 access
		/// </summary>
		constexpr OpAccess GetOp4Access() const;
		/// <summary>
		/// Gets operand access
		/// </summary>
		/// <param name="operand">Operand number, 0-4</param>
		/// <returns></returns>
		constexpr OpAccess GetOpAccess(std::int32_t operand) const;

		constexpr InstructionInfo() = default;
	};


	constexpr InstructionInfo::InstructionInfo(bool dummy)
	{
		usedRegisters = std::vector<UsedRegister>();
		usedRegisters.reserve(InstructionInfoInternal::InstrInfoConstants::DefaultUsedRegisterCollCapacity);
		usedMemoryLocations = std::vector<UsedMemory>();
		usedMemoryLocations.reserve(InstructionInfoInternal::InstrInfoConstants::DefaultUsedMemoryCollCapacity);
		opAccesses[0] = 0;
		opAccesses[1] = 0;
		opAccesses[2] = 0;
		opAccesses[3] = 0;
		opAccesses[4] = 0;
		static_assert(IcedConstants::MaxOpCount == 5);
	}

	constexpr const std::vector<UsedRegister>& InstructionInfo::GetUsedRegisters() const
	{
		return usedRegisters;
	}

	constexpr const std::vector<UsedMemory>& InstructionInfo::GetUsedMemory() const
	{
		return usedMemoryLocations;
	}

	constexpr OpAccess InstructionInfo::GetOp0Access() const
	{
		return (OpAccess)opAccesses[0];
	}

	constexpr OpAccess InstructionInfo::GetOp1Access() const
	{
		return (OpAccess)opAccesses[1];
	}

	constexpr OpAccess InstructionInfo::GetOp2Access() const
	{
		return (OpAccess)opAccesses[2];
	}

	constexpr OpAccess InstructionInfo::GetOp3Access() const
	{
		return (OpAccess)opAccesses[3];
	}

	constexpr OpAccess InstructionInfo::GetOp4Access() const
	{
		return (OpAccess)opAccesses[4];
	}

	constexpr OpAccess InstructionInfo::GetOpAccess(std::int32_t operand) const
	{
		switch (operand)
		{
		case 0:
			return GetOp0Access();
		case 1:
			return GetOp1Access();
		case 2:
			return GetOp2Access();
		case 3:
			return GetOp3Access();
		case 4:
			return GetOp4Access();
		default:
			throw std::invalid_argument("operand out of range.");
		}
	}
}
