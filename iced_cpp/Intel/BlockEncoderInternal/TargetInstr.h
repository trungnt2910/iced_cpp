// C# helper headers

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
#include "Block.h"

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::BlockEncoderInternal
{
	class Instr;
	class Block;
	/* readonly */
	class TargetInstr
	{
		/* readonly */
	private:
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: Instr? instruction;
		std::shared_ptr<Instr> instruction = nullptr;
		/* readonly */
		std::uint64_t address = 0;
	public:
		TargetInstr(std::shared_ptr<Instr> instruction);
		TargetInstr(std::uint64_t address);
		bool IsInBlock(std::shared_ptr<Block> block);
		std::uint64_t GetAddress();

		TargetInstr() = default;
	};
}
