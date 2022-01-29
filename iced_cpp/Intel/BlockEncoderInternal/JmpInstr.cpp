// C# helper headers




// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "JmpInstr.h"
#include "../Iced.Intel.InstructionInfoExtensions.h"
#include "../../NRT_Helpers.h"

namespace Iced::Intel::BlockEncoderInternal
{

	JmpInstr::JmpInstr(BlockEncoder* blockEncoder, std::shared_ptr<class Block> block, const Instruction& instruction) : Instr(block, instruction.GetIP())
	{
		bitness = blockEncoder->GetBitness();
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
			instrCopy.InternalSetCodeNoCheck(Iced::Intel::InstructionInfoExtensions::ToShortBranch(instruction.GetCode()));
			instrCopy.SetNearBranch64(0);
			shortInstructionSize = blockEncoder->GetInstructionSize(instrCopy, 0);
			instrCopy = instruction;
			instrCopy.InternalSetCodeNoCheck(Iced::Intel::InstructionInfoExtensions::ToNearBranch(instruction.GetCode()));
			instrCopy.SetNearBranch64(0);
			nearInstructionSize = blockEncoder->GetInstructionSize(instrCopy, 0);
			if (blockEncoder->GetBitness() == 64)
			{
				// Make sure it's not shorter than the real instruction. It can happen if there are extra prefixes.
				Size = std::max(nearInstructionSize, CallOrJmpPointerDataInstructionSize64);
			}
			else
			{
				Size = nearInstructionSize;
			}
		}
	}

	void JmpInstr::Initialize(BlockEncoder* blockEncoder)
	{
		targetInstr = blockEncoder->GetTarget(instruction.GetNearBranchTarget());
		TryOptimize(0);
	}

	bool JmpInstr::Optimize(std::uint64_t gained)
	{
		return TryOptimize(gained);
	}

	bool JmpInstr::TryOptimize(std::uint64_t gained)
	{
		auto Block = this->Block.lock();
		if (!Block)
		{
			throw std::runtime_error("block has been destroyed.");
		}
		if (instrKind == InstrKind::Unchanged || instrKind == InstrKind::Short)
		{
			return false;
		}
		auto targetAddress = targetInstr.GetAddress();
		auto nextRip = IP + shortInstructionSize;
		std::int64_t diff = static_cast<std::int64_t>(targetAddress - nextRip);
		diff = CorrectDiff(targetInstr.IsInBlock(Block), diff, gained);
		if (std::numeric_limits<std::int8_t>::min() <= diff && diff <= std::numeric_limits<std::int8_t>::max())
		{
			if (pointerData != nullptr)
			{
				pointerData->IsValid = false;
			}
			instrKind = InstrKind::Short;
			Size = shortInstructionSize;
			return true;
		}
		// If it's in the same block, we assume the target is at most 2GB away.
		bool useNear = bitness != 64 || targetInstr.IsInBlock(Block);
		if (!useNear)
		{
			targetAddress = targetInstr.GetAddress();
			nextRip = IP + nearInstructionSize;
			diff = static_cast<std::int64_t>(targetAddress - nextRip);
			diff = CorrectDiff(targetInstr.IsInBlock(Block), diff, gained);
			useNear = std::numeric_limits<std::int32_t>::min() <= diff && diff <= std::numeric_limits<std::int32_t>::max();
		}
		if (useNear)
		{
			if (pointerData != nullptr)
			{
				pointerData->IsValid = false;
			}
			instrKind = InstrKind::Near;
			Size = nearInstructionSize;
			return true;
		}
		if (pointerData == nullptr)
		{
			pointerData = Block->AllocPointerLocation();
		}
		instrKind = InstrKind::Long;
		return false;
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override string? TryEncode(Encoder encoder, out ConstantOffsets constantOffsets, out bool isOriginalInstruction)
	std::string JmpInstr::TryEncode(Encoder& encoder, ConstantOffsets& constantOffsets, bool& isOriginalInstruction)
	{
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: string? errorMessage;
		std::string errorMessage;
		switch (instrKind)
		{
		case InstrKind::Unchanged:
		case InstrKind::Short:
		case InstrKind::Near:
			isOriginalInstruction = true;
			if (instrKind == InstrKind::Unchanged)
			{
				// nothing
			}
			else if (instrKind == InstrKind::Short)
			{
				instruction.InternalSetCodeNoCheck(Iced::Intel::InstructionInfoExtensions::ToShortBranch(instruction.GetCode()));
			}
			else
			{
				assert(instrKind == InstrKind::Near);
				instruction.InternalSetCodeNoCheck(Iced::Intel::InstructionInfoExtensions::ToNearBranch(instruction.GetCode()));
			}
			instruction.SetNearBranch64(targetInstr.GetAddress());
			std::uint32_t _;
			if (!encoder.TryEncode(instruction, IP, _, errorMessage))
			{
				constantOffsets = Iced::Intel::ConstantOffsets();
				return CreateErrorMessage(errorMessage, instruction);
			}
			constantOffsets = encoder.GetConstantOffsets();
			return "";
		case InstrKind::Long:
			System::Diagnostics::Debug2::Assert(pointerData != nullptr);
			isOriginalInstruction = false;
			constantOffsets = Iced::Intel::ConstantOffsets();
			pointerData->Data = targetInstr.GetAddress();
			errorMessage = EncodeBranchToPointerData(encoder, false, IP, pointerData, _, Size);
			if (errorMessage != "")
			{
				return CreateErrorMessage(errorMessage, instruction);
			}
			return "";
		case InstrKind::Uninitialized:
		default:
			throw std::runtime_error("invalid operation");
		}
	}
}
