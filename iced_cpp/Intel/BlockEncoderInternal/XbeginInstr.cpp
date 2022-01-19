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

#include "XbeginInstr.h"
#include "../Code.g.h"

namespace Iced::Intel::BlockEncoderInternal
{

	XbeginInstr::XbeginInstr(BlockEncoder* blockEncoder, std::shared_ptr<class Block> block, const Instruction& instruction) : Instr(block, instruction.GetIP())
	{
		this->instruction = instruction;
		instrKind = InstrKind::Uninitialized;
		Instruction instrCopy;
		if (!blockEncoder->GetFixBranches())
		{
			instrKind = InstrKind::Unchanged;
			instrCopy = instruction;
			instrCopy.SetNearBranch64(0);
			Size = blockEncoder->GetInstructionSize(instrCopy, 0);
		}
		else
		{
			instrCopy = instruction;
			instrCopy.InternalSetCodeNoCheck(Code::Xbegin_rel16);
			instrCopy.SetNearBranch64(0);
			shortInstructionSize = blockEncoder->GetInstructionSize(instrCopy, 0);
			instrCopy = instruction;
			instrCopy.InternalSetCodeNoCheck(Code::Xbegin_rel32);
			instrCopy.SetNearBranch64(0);
			nearInstructionSize = blockEncoder->GetInstructionSize(instrCopy, 0);
			Size = nearInstructionSize;
		}
	}

	void XbeginInstr::Initialize(BlockEncoder* blockEncoder)
	{
		targetInstr = blockEncoder->GetTarget(instruction.GetNearBranchTarget());
		TryOptimize(0);
	}

	bool XbeginInstr::Optimize(std::uint64_t gained)
	{
		return TryOptimize(gained);
	}

	bool XbeginInstr::TryOptimize(std::uint64_t gained)
	{
		auto Block = this->Block.lock();
		if (!Block)
		{
			throw std::runtime_error("block has been destroyed.");
		}
		if (instrKind == InstrKind::Unchanged || instrKind == InstrKind::Rel16)
		{
			return false;
		}
		auto targetAddress = targetInstr.GetAddress();
		auto nextRip = IP + shortInstructionSize;
		std::int64_t diff = static_cast<std::int64_t>(targetAddress - nextRip);
		diff = CorrectDiff(targetInstr.IsInBlock(Block), diff, gained);
		if (std::numeric_limits<std::int16_t>::min() <= diff && diff <= std::numeric_limits<std::int16_t>::max())
		{
			instrKind = InstrKind::Rel16;
			Size = shortInstructionSize;
			return true;
		}
		instrKind = InstrKind::Rel32;
		Size = nearInstructionSize;
		return false;
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override string? TryEncode(Encoder encoder, out ConstantOffsets constantOffsets, out bool isOriginalInstruction)
	std::string XbeginInstr::TryEncode(Encoder& encoder, ConstantOffsets& constantOffsets, bool& isOriginalInstruction)
	{
		switch (instrKind)
		{
		case InstrKind::Unchanged:
		case InstrKind::Rel16:
		case InstrKind::Rel32:
		{
			isOriginalInstruction = true;
			if (instrKind == InstrKind::Unchanged)
			{
				// nothing
			}
			else if (instrKind == InstrKind::Rel16)
			{
				instruction.InternalSetCodeNoCheck(Code::Xbegin_rel16);
			}
			else
			{
				assert(instrKind == InstrKind::Rel32);
				instruction.InternalSetCodeNoCheck(Code::Xbegin_rel32);
			}
			instruction.SetNearBranch64(targetInstr.GetAddress());
			std::string errorMessage;
			std::uint32_t _;
			if (!encoder.TryEncode(instruction, IP, _, errorMessage))
			{
				constantOffsets = Iced::Intel::ConstantOffsets();
				return CreateErrorMessage(errorMessage, instruction);
			}
			constantOffsets = encoder.GetConstantOffsets();
			return "";
		}
		case InstrKind::Uninitialized:
		default:
			throw InvalidOperationException();
		}
	}
}
