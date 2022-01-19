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
#include "../BlockEncoder.h"
#include "Block.h"
#include "../ConstantOffsets.h"
#include "../Encoder.h"
#include <string>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::BlockEncoderInternal
{
	class Block;
	/// <summary>
	/// Simple instruction that doesn't need fixing, i.e., it's not IP relative (no branch instruction, no IP relative memory operand)
	/// </summary>
	class SimpleInstr final : public Instr
	{
	private:
		Instruction instruction;
	public:
		SimpleInstr(BlockEncoder* blockEncoder, class Block* block, const Instruction& instruction);
		void Initialize(BlockEncoder* blockEncoder) override;
		bool Optimize(std::uint64_t gained) override;
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: public override string? TryEncode(Encoder encoder, out ConstantOffsets constantOffsets, out bool isOriginalInstruction)
		std::string TryEncode(Encoder* encoder, ConstantOffsets& constantOffsets, bool& isOriginalInstruction) override;
	};
}
