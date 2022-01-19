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

	bool TargetInstr::IsInBlock(Block* block)
	{
		return instruction == nullptr ? false : instruction->Block == block;
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
