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

#include "UsedRegister.h"
#include "InstructionInfoInternal/SimpleList.h"
#include "UsedMemory.h"
#include "OpAccess.g.h"
#include <vector>
#include <any>
#include <csharp/exceptionhelper.h>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Iced::Intel { class UsedRegisterIterator; }
namespace Iced::Intel { class UsedMemoryIterator; }

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
using namespace Iced::Intel::InstructionInfoInternal;
namespace Iced::Intel
{
	/// <summary>
	/// Contains information about an instruction, eg. read/written registers, read/written <c>RFLAGS</c> bits, <c>CPUID</c> feature bit, etc
	/// </summary>
	class InstructionInfo
	{
	public:
		SimpleList<UsedRegister> usedRegisters;
		SimpleList<UsedMemory> usedMemoryLocations;
		//C# TO C++ CONVERTER TODO TASK: C# 'unsafe' code is not converted by C# to C++ Converter:
		//  internal unsafe fixed byte opAccesses[IcedConstants.MaxOpCount];
		InstructionInfo(bool dummy);
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
		UsedRegisterIterator GetUsedRegisters();
		/// <summary>
		/// Gets a struct iterator that returns all accessed memory locations
		/// </summary>
		/// <returns></returns>
		UsedMemoryIterator GetUsedMemory();
	public:
		class UsedRegisterIterator : public std::vector<UsedRegister>, public IEnumerator<UsedRegister>
		{
			/* readonly */
		private:
			std::vector<UsedRegister> usedRegisters;
			/* readonly */
			std::uint32_t length = 0;
			std::int32_t index = 0;
		public:
			UsedRegisterIterator(std::vector<UsedRegister>& usedRegisters, std::uint32_t length);
			UsedRegisterIterator GetEnumerator();
			UsedRegister GetCurrent() const override;
			bool MoveNext() override;
			IEnumerator<UsedRegister>* IEnumerable_GetEnumerator() override;
			System::Collections::IEnumerator* IEnumerable_GetEnumerator() override;
		private:
			UsedRegister IEnumerator;
			std::any IEnumerator;
		public:
			bool IEnumerator_MoveNext() override;
			void Reset() override;
			~UsedRegisterIterator();

			UsedRegisterIterator() = default;
		};
	public:
		class UsedMemoryIterator : public std::vector<UsedMemory>, public IEnumerator<UsedMemory>
		{
			/* readonly */
		private:
			std::vector<UsedMemory> usedMemoryLocations;
			/* readonly */
			std::uint32_t length = 0;
			std::int32_t index = 0;
		public:
			UsedMemoryIterator(std::vector<UsedMemory>& usedMemoryLocations, std::uint32_t length);
			UsedMemoryIterator GetEnumerator();
			UsedMemory GetCurrent() const override;
			bool MoveNext() override;
			IEnumerator<UsedMemory>* IEnumerable_GetEnumerator() override;
			System::Collections::IEnumerator* IEnumerable_GetEnumerator() override;
		private:
			UsedMemory IEnumerator;
			std::any IEnumerator;
		public:
			bool IEnumerator_MoveNext() override;
			void Reset() override;
			~UsedMemoryIterator();

			UsedMemoryIterator() = default;
		};
		/// <summary>
		/// Operand #0 access
		/// </summary>
	public:
		OpAccess GetOp0Access() const;
		/// <summary>
		/// Operand #1 access
		/// </summary>
		OpAccess GetOp1Access() const;
		/// <summary>
		/// Operand #2 access
		/// </summary>
		OpAccess GetOp2Access() const;
		/// <summary>
		/// Operand #3 access
		/// </summary>
		OpAccess GetOp3Access() const;
		/// <summary>
		/// Operand #4 access
		/// </summary>
		OpAccess GetOp4Access() const;
		/// <summary>
		/// Gets operand access
		/// </summary>
		/// <param name="operand">Operand number, 0-4</param>
		/// <returns></returns>
		OpAccess GetOpAccess(std::int32_t operand);

		InstructionInfo() = default;
	};
}
