// C# helper headers
#include <csharp/classes.h>
#include <csharp/enum.h>



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
#include "Block.h"
#include "../BlockEncoder.h"
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
	/// <summary>
	/// Jmp instruction
	/// </summary>
	class JmpInstr final : public Instr
	{

		enum class InstrKind
		{
			Unchanged,
			Short,
			Near,
			Long,
			Uninitialized
		};

		DEFINE_COMP_FRIEND(InstrKind)
			DEFINE_ARITH_FRIEND(InstrKind)
		/* readonly */
	private:
		std::int32_t bitness = 0;
		Instruction instruction;
		TargetInstr targetInstr;
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: BlockData? pointerData;
		BlockData* pointerData;
		InstrKind instrKind = static_cast<InstrKind>(0);
		/* readonly */
		std::uint32_t shortInstructionSize = 0;
		/* readonly */
		std::uint32_t nearInstructionSize = 0;
	private:

	public:
		JmpInstr(BlockEncoder* blockEncoder, std::shared_ptr<class Block> block, const Instruction& instruction);
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
