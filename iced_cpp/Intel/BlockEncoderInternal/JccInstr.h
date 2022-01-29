// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include "Instr.h"
#include "../Iced.Intel.Instruction.h"
#include "TargetInstr.h"
#include "Block.h"
#include "../BlockEncoder.h"
#include "../ConstantOffsets.h"
#include "../Encoder.h"
#include "../Code.g.h"
#include "../Internal/Enum.h"
#include <string>
#include <limits>
#include <cassert>

namespace Iced::Intel::BlockEncoderInternal
{
	class Block;

	/// <summary>
	/// Jcc instruction
	/// </summary>
	class JccInstr final : public Instr
	{
	private:
		enum class InstrKind
		{
			Unchanged,
			Short,
			Near,
			Long,
			Uninitialized
		};

		ICED_DEFINE_COMP_FRIEND(InstrKind)
		ICED_DEFINE_ARITH_FRIEND(InstrKind)
	private:
		std::int32_t bitness = 0;
		Instruction instruction;
		TargetInstr targetInstr;
		BlockData* pointerData = nullptr;
		InstrKind instrKind = static_cast<InstrKind>(0);
		std::uint32_t shortInstructionSize = 0;
		std::uint32_t nearInstructionSize = 0;
		std::uint32_t longInstructionSize64 = 0;
		static std::uint32_t GetLongInstructionSize64(const Instruction& instruction);

	public:
		JccInstr(BlockEncoder* blockEncoder, std::shared_ptr<class Block> block, const Instruction& instruction);
		void Initialize(BlockEncoder* blockEncoder) override;
		bool Optimize(std::uint64_t gained) override;
	private:
		bool TryOptimize(std::uint64_t gained);
	public:
		std::string TryEncode(Encoder& encoder, ConstantOffsets& constantOffsets, bool& isOriginalInstruction) override;
	private:
		static Code ShortBrToNativeBr(Code code, std::int32_t bitness);
	};
}
