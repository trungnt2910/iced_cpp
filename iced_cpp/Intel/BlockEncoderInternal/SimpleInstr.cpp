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

#include "SimpleInstr.h"

namespace Iced::Intel::BlockEncoderInternal
{

	SimpleInstr::SimpleInstr(BlockEncoder* blockEncoder, class Block* block, Instruction const instruction) : Instr(block, instruction.GetIP())
	{
		this->instruction = instruction;
		Size = blockEncoder->GetInstructionSize(instruction, instruction.GetIP());
	}

	void SimpleInstr::Initialize(BlockEncoder* blockEncoder)
	{
	}

	bool SimpleInstr::Optimize(std::uint64_t gained)
	{
		return false;
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override string? TryEncode(Encoder encoder, out ConstantOffsets constantOffsets, out bool isOriginalInstruction)
	std::string SimpleInstr::TryEncode(Encoder* encoder, ConstantOffsets& constantOffsets, bool& isOriginalInstruction)
	{
		isOriginalInstruction = true;
		std::string errorMessage;
		std::uint32_t _;
		if (!encoder->TryEncode(instruction, IP, _, errorMessage))
		{
			constantOffsets = Iced::Intel::ConstantOffsets();
			return CreateErrorMessage(errorMessage, instruction);
		}
		constantOffsets = encoder->GetConstantOffsets();
		return "";
	}
}
