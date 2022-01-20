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

#include "InstructionInfo.h"
#include "CodeSize.g.h"
#include "Register.g.h"
#include "InstructionInfoInternal/InfoHandlerFlags.h"
#include "Iced.Intel.Instruction.h"
#include "OpAccess.g.h"
#include "MemorySize.g.h"
#include <vector>
#include <limits>
#include <csharp/exceptionhelper.h>
#include <cassert>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
using namespace Iced::Intel::InstructionInfoInternal;
namespace Iced::Intel
{
	/// <summary>
	/// Instruction info options used by <see cref="InstructionInfoFactory"/>
	/// </summary>
	enum class InstructionInfoOptions : uint
	{
		/// <summary>
		/// No option is enabled
		/// </summary>
		None = 0,

		/// <summary>
		/// Don't include memory usage, i.e., <see cref="InstructionInfo.GetUsedMemory"/> will return an empty iterator. All
		/// registers that are used by memory operands are still returned by <see cref="InstructionInfo.GetUsedRegisters"/>.
		/// </summary>
		NoMemoryUsage = 0x00000001,

		/// <summary>
		/// Don't include register usage, i.e., <see cref="InstructionInfo.GetUsedRegisters"/> will return an empty iterator
		/// </summary>
		NoRegisterUsage = 0x00000002
	};
	DEFINE_FLAGS(InstructionInfoOptions)
		DEFINE_COMP(InstructionInfoOptions)
		DEFINE_ARITH(InstructionInfoOptions)

	/// <summary>
	/// Creates <see cref="InstructionInfo"/>s.
	/// <br/>
	/// If you don't need memory and register usage, it's faster to call <see cref="Instruction"/> and <see cref="Code"/>
	/// methods/properties, eg. <see cref="Instruction.FlowControl"/>, etc instead of getting that info from this class.
	/// </summary>
	class InstructionInfoFactory final
	{
	private:
		static constexpr std::int32_t defaultRegisterArrayCount = 2;
		static constexpr std::int32_t defaultMemoryArrayCount = 1;
		InstructionInfo info;
	private:
		enum class Flags : int
		{
			None = 0,
			NoMemoryUsage = 0x00000001,
			NoRegisterUsage = 0x00000002,
			Is64Bit = 0x00000004,
			ZeroExtVecRegs = 0x00000008
		};
		DEFINE_FLAGS_FRIEND(Flags)
			DEFINE_COMP_FRIEND(Flags)
			DEFINE_ARITH_FRIEND(Flags)

			/// <summary>
			/// Constructor
			/// </summary>
	public:
		InstructionInfoFactory();
		/// <summary>
		/// Creates an <see cref="InstructionInfo"/>. The return value is only valid until this instance creates a new <see cref="InstructionInfo"/> value.
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <returns></returns>
		const InstructionInfo& GetInfo(const Instruction& instruction);
		/// <summary>
		/// Creates an <see cref="InstructionInfo"/>. The return value is only valid until this instance creates a new <see cref="InstructionInfo"/> value.
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="options">Options</param>
		/// <returns></returns>
		const InstructionInfo& GetInfo(const Instruction& instruction, InstructionInfoOptions options);
	private:
		static Register GetXSP(CodeSize codeSize, std::uint64_t& xspMask, CodeSize& addressSize);
		void AddImpliedAccesses(ImpliedAccess impliedAccess, const Instruction& instruction, Flags flags);
		static Register GetARDI(Instruction instruction);
		static Register GetSegDefaultDS(Instruction instruction);
		void CommandPush(const Instruction& instruction, Flags flags, std::int32_t count, std::uint32_t opSize);
		void CommandPop(const Instruction& instruction, Flags flags, std::int32_t count, std::uint32_t opSize);
		void CommandPopRm(const Instruction& instruction, Flags flags, std::uint32_t opSize);
		void CommandPusha(const Instruction& instruction, Flags flags, std::uint32_t opSize);
		void CommandPopa(const Instruction& instruction, Flags flags, std::uint32_t opSize);
		void CommandIns(const Instruction& instruction, Flags flags);
		void CommandOuts(const Instruction& instruction, Flags flags);
		void CommandMovs(const Instruction& instruction, Flags flags);
		void CommandCmps(const Instruction& instruction, Flags flags);
		void CommandStos(const Instruction& instruction, Flags flags);
		void CommandLods(const Instruction& instruction, Flags flags);
		void CommandScas(const Instruction& instruction, Flags flags);
		void CommandXstore(const Instruction& instruction, Flags flags, std::uint32_t size);
		void CommandEnter(const Instruction& instruction, Flags flags, std::uint32_t opSize);
		void CommandLeave(const Instruction& instruction, Flags flags, std::uint32_t opSize);
		void CommandClearRflags(const Instruction& instruction, Flags flags);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] static bool IsClearInstr(in Instruction instruction)
		static bool IsClearInstr(const Instruction& instruction);
		void CommandClearRegRegmem(const Instruction& instruction, Flags flags);
		void CommandClearRegRegRegmem(const Instruction& instruction, Flags flags);
		void CommandArpl(const Instruction& instruction, Flags flags);
		void CommandLastGpr(const Instruction& instruction, Flags flags, Register baseReg);
		void CommandLea(const Instruction& instruction, Flags flags);
		void CommandEmmi(const Instruction& instruction, Flags flags, OpAccess opAccess);
		void CommandMemDispl(Flags flags, std::int32_t extraDispl);
		static std::int32_t TryGetGpr163264Index(Register register_);
		void AddMemory(Register segReg, Register baseReg, Register indexReg, std::int32_t scale, std::uint64_t displ, MemorySize memorySize, OpAccess access, CodeSize addressSize, std::int32_t vsibSize);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] void AddMemorySegmentRegister(Flags flags, Register seg, OpAccess access)
		void AddMemorySegmentRegister(Flags flags, Register seg, OpAccess access);
		void AddRegister(Flags flags, Register reg, OpAccess access);
		const InstructionInfo& Create(const Instruction& instruction, InstructionInfoOptions options);
	};
}
