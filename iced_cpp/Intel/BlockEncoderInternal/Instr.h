// C# helper headers




// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#pragma once

#include "Block.h"
#include "../BlockEncoder.h"
#include "../ConstantOffsets.h"
#include "../Encoder.h"
#include "../Iced.Intel.Instruction.h"
#include <string>
#include <limits>
#include <format>
#include <cassert>

namespace Iced::Intel { class BlockEncoder;  }

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::BlockEncoderInternal
{
	class BlockData;
	class Instr
	{
	public:
		std::weak_ptr<class Block> Block;
		std::uint32_t Size = 0;
		std::uint64_t IP = 0;
		std::uint64_t OrigIP = 0;
		// 6 = FF 15 XXXXXXXX = call qword ptr [rip+mem_target]
	protected:
		static constexpr std::uint32_t CallOrJmpPointerDataInstructionSize64 = 6;
		Instr(std::shared_ptr<class Block> block, std::uint64_t origIp);
		/// <summary>
		/// Initializes the target address and tries to optimize the instruction
		/// </summary>
	public:
		virtual void Initialize(::Iced::Intel::BlockEncoder* blockEncoder) = 0;
		/// <summary>
		/// Returns <see langword="true"/> if the instruction was updated to a shorter instruction, <see langword="false"/> if nothing changed
		/// </summary>
		/// <returns></returns>
		virtual bool Optimize(std::uint64_t gained) = 0;
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: public abstract string? TryEncode(Encoder encoder, out ConstantOffsets constantOffsets, out bool isOriginalInstruction);
		virtual std::string TryEncode(Encoder& encoder, ConstantOffsets& constantOffsets, bool& isOriginalInstruction) = 0;
	protected:
		static std::string CreateErrorMessage(const std::string& errorMessage, const Instruction& instruction);
	public:
		static std::shared_ptr<Instr> Create(::Iced::Intel::BlockEncoder* blockEncoder, std::shared_ptr<class Block> block, const Instruction& instruction);
	protected:
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: protected string? EncodeBranchToPointerData(Encoder encoder, bool isCall, ulong ip, BlockData pointerData, out uint size, uint minSize)
		std::string EncodeBranchToPointerData(Encoder& encoder, bool isCall, std::uint64_t ip, BlockData* pointerData, std::uint32_t& size, std::uint32_t minSize);
		static std::int64_t CorrectDiff(bool inBlock, std::int64_t diff, std::uint64_t gained);
	};
}
