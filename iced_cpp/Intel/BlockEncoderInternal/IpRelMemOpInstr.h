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

#include "Instr.h"
#include "../Iced.Intel.Instruction.h"
#include "TargetInstr.h"
#include "../BlockEncoder.h"
#include "Block.h"
#include "../ConstantOffsets.h"
#include "../Encoder.h"
#include <string>
#include <limits>
#include <csharp/exceptionhelper.h>
#include <cassert>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::BlockEncoderInternal
{
	class Block;
	/// <summary>
	/// Instruction with a memory operand that is RIP/EIP relative
	/// </summary>
	class IpRelMemOpInstr final : public Instr
	{
	private:
		enum class InstrKind
		{
			Unchanged,
			Rip,
			Eip,
			Long,
			Uninitialized
		};

		DEFINE_COMP_FRIEND(InstrKind)
			DEFINE_ARITH_FRIEND(InstrKind)
	private:
		Instruction instruction;
		InstrKind instrKind = static_cast<InstrKind>(0);
		/* readonly */
		std::uint32_t eipInstructionSize = 0;
		/* readonly */
		std::uint32_t ripInstructionSize = 0;
		TargetInstr targetInstr;

	public:
		IpRelMemOpInstr(BlockEncoder* blockEncoder, std::shared_ptr<class Block> block, const Instruction& instruction);
		void Initialize(BlockEncoder* blockEncoder) override;
		bool Optimize(std::uint64_t gained) override;
	private:
		bool TryOptimize(std::uint64_t gained);
	public:
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: public override string? TryEncode(Encoder encoder, out ConstantOffsets constantOffsets, out bool isOriginalInstruction)
		std::string TryEncode(Encoder& encoder, ConstantOffsets& constantOffsets, bool& isOriginalInstruction) override;
	};
}
