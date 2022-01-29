// C# helper headers




// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "TargetInstr.h"

namespace Iced::Intel::BlockEncoderInternal
{

	TargetInstr::TargetInstr(std::shared_ptr<Instr> instruction)
	{
		this->instruction = instruction;
		address = 0;
	}

	TargetInstr::TargetInstr(std::uint64_t address)
	{
		instruction = nullptr;
		this->address = address;
	}

	bool TargetInstr::IsInBlock(std::shared_ptr<Block> block)
	{
		return instruction == nullptr ? false : instruction->Block.lock() == block;
	}

	std::uint64_t TargetInstr::GetAddress()
	{
		auto instruction = this->instruction;
		if (instruction == nullptr)
		{
			return address;
		}
		return instruction->IP;
	}
}
