// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

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
#include <cassert>

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

		ICED_DEFINE_COMP_FRIEND(InstrKind)
		ICED_DEFINE_ARITH_FRIEND(InstrKind)

	private:
		Instruction instruction;
		InstrKind instrKind = static_cast<InstrKind>(0);
		std::uint32_t eipInstructionSize = 0;
		std::uint32_t ripInstructionSize = 0;
		TargetInstr targetInstr;

	public:
		IpRelMemOpInstr(BlockEncoder* blockEncoder, std::shared_ptr<class Block> block, const Instruction& instruction);
		void Initialize(BlockEncoder* blockEncoder) override;
		bool Optimize(std::uint64_t gained) override;
	private:
		bool TryOptimize(std::uint64_t gained);
	public:
		std::string TryEncode(Encoder& encoder, ConstantOffsets& constantOffsets, bool& isOriginalInstruction) override;
	};
}
