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

#include "CallInstr.h"
#include "../../NRT_Helpers.h"

namespace Iced::Intel::BlockEncoderInternal
{

	CallInstr::CallInstr(BlockEncoder* blockEncoder, std::shared_ptr<class Block> block, const Instruction& instruction) : Instr(block, instruction.GetIP())
	{
		bitness = blockEncoder->GetBitness();
		this->instruction = instruction;
		auto instrCopy = instruction;
		instrCopy.SetNearBranch64(0);
		origInstructionSize = blockEncoder->GetInstructionSize(instrCopy, 0);
		if (!blockEncoder->GetFixBranches())
		{
			Size = origInstructionSize;
			useOrigInstruction = true;
			done = true;
		}
		else if (blockEncoder->GetBitness() == 64)
		{
			// Make sure it's not shorter than the real instruction. It can happen if there are extra prefixes.
			Size = std::max(origInstructionSize, CallOrJmpPointerDataInstructionSize64);
		}
		else
		{
			Size = origInstructionSize;
		}
	}

	void CallInstr::Initialize(BlockEncoder* blockEncoder)
	{
		targetInstr = blockEncoder->GetTarget(instruction.GetNearBranchTarget());
		TryOptimize(0);
	}

	bool CallInstr::Optimize(std::uint64_t gained)
	{
		return TryOptimize(gained);
	}

	bool CallInstr::TryOptimize(std::uint64_t gained)
	{
		auto Block = this->Block.lock();
		if (!Block)
		{
			throw std::runtime_error("block has been destroyed.");
		}
		if (done)
		{
			return false;
		}
		// If it's in the same block, we assume the target is at most 2GB away.
		bool useShort = bitness != 64 || targetInstr.IsInBlock(Block);
		if (!useShort)
		{
			auto targetAddress = targetInstr.GetAddress();
			auto nextRip = IP + origInstructionSize;
			std::int64_t diff = static_cast<std::int64_t>(targetAddress - nextRip);
			diff = CorrectDiff(targetInstr.IsInBlock(Block), diff, gained);
			useShort = std::numeric_limits<std::int32_t>::min() <= diff && diff <= std::numeric_limits<std::int32_t>::max();
		}
		if (useShort)
		{
			if (pointerData != nullptr)
			{
				pointerData->IsValid = false;
			}
			Size = origInstructionSize;
			useOrigInstruction = true;
			done = true;
			return true;
		}
		if (pointerData == nullptr)
		{
			pointerData = Block->AllocPointerLocation();
		}
		return false;
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override string? TryEncode(Encoder encoder, out ConstantOffsets constantOffsets, out bool isOriginalInstruction)
	std::string CallInstr::TryEncode(Encoder& encoder, ConstantOffsets& constantOffsets, bool& isOriginalInstruction)
	{
		if (useOrigInstruction)
		{
			isOriginalInstruction = true;
			instruction.SetNearBranch64(targetInstr.GetAddress());
			std::string errorMessage;
			uint32_t _;
			if (!encoder.TryEncode(instruction, IP, _, errorMessage))
			{
				constantOffsets = Iced::Intel::ConstantOffsets();
				return CreateErrorMessage(errorMessage, instruction);
			}
			constantOffsets = encoder.GetConstantOffsets();
			return "";
		}
		else
		{
			System::Diagnostics::Debug2::Assert(pointerData != nullptr);
			isOriginalInstruction = false;
			constantOffsets = Iced::Intel::ConstantOffsets();
			pointerData->Data = targetInstr.GetAddress();
			uint32_t _;
			auto errorMessage = EncodeBranchToPointerData(encoder, true, IP, pointerData, _, Size);
			if (errorMessage != "")
			{
				return CreateErrorMessage(errorMessage, instruction);
			}
			return "";
		}
	}
}
