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

#include "IpRelMemOpInstr.h"
#include "../Register.g.h"

namespace Iced::Intel::BlockEncoderInternal
{

	IpRelMemOpInstr::IpRelMemOpInstr(BlockEncoder* blockEncoder, Block* block, Instruction const instruction) : Instr(block, instruction.GetIP())
	{
		assert(instruction.IsIPRelativeMemoryOperand());
		this->instruction = instruction;
		instrKind = InstrKind::Uninitialized;
		auto instrCopy = instruction;
		instrCopy.SetMemoryBase(Register::RIP);
		instrCopy.SetMemoryDisplacement64(0);
		ripInstructionSize = blockEncoder->GetInstructionSize(instrCopy, instrCopy.GetIPRelativeMemoryAddress());
		instrCopy.SetMemoryBase(Register::EIP);
		eipInstructionSize = blockEncoder->GetInstructionSize(instrCopy, instrCopy.GetIPRelativeMemoryAddress());
		assert(eipInstructionSize >= ripInstructionSize);
		Size = eipInstructionSize;
	}

	void IpRelMemOpInstr::Initialize(BlockEncoder* blockEncoder)
	{
		targetInstr = blockEncoder->GetTarget(instruction.GetIPRelativeMemoryAddress());
		TryOptimize(0);
	}

	bool IpRelMemOpInstr::Optimize(std::uint64_t gained)
	{
		return TryOptimize(gained);
	}

	bool IpRelMemOpInstr::TryOptimize(std::uint64_t gained)
	{
		if (instrKind == InstrKind::Unchanged || instrKind == InstrKind::Rip || instrKind == InstrKind::Eip)
		{
			return false;
		}
		// If it's in the same block, we assume the target is at most 2GB away.
		bool useRip = targetInstr.IsInBlock(Block);
		auto targetAddress = targetInstr.GetAddress();
		if (!useRip)
		{
			auto nextRip = IP + ripInstructionSize;
			std::int64_t diff = static_cast<std::int64_t>(targetAddress - nextRip);
			diff = CorrectDiff(targetInstr.IsInBlock(Block), diff, gained);
			useRip = std::numeric_limits<std::int32_t>::min() <= diff && diff <= std::numeric_limits<std::int32_t>::max();
		}
		if (useRip)
		{
			Size = ripInstructionSize;
			instrKind = InstrKind::Rip;
			return true;
		}
		// If it's in the lower 4GB we can use EIP relative addressing
		if (targetAddress <= std::numeric_limits<std::uint32_t>::max())
		{
			Size = eipInstructionSize;
			instrKind = InstrKind::Eip;
			return true;
		}
		instrKind = InstrKind::Long;
		return false;
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override string? TryEncode(Encoder encoder, out ConstantOffsets constantOffsets, out bool isOriginalInstruction)
	std::string IpRelMemOpInstr::TryEncode(Encoder* encoder, ConstantOffsets& constantOffsets, bool& isOriginalInstruction)
	{
		switch (instrKind)
		{
		case InstrKind::Unchanged:
		case InstrKind::Rip:
		case InstrKind::Eip:
		{
			isOriginalInstruction = true;
			if (instrKind == InstrKind::Rip)
			{
				instruction.SetMemoryBase(Register::RIP);
			}
			else if (instrKind == InstrKind::Eip)
			{
				instruction.SetMemoryBase(Register::EIP);
			}
			else
			{
				assert(instrKind == InstrKind::Unchanged);
			}
			auto targetAddress = targetInstr.GetAddress();
			instruction.SetMemoryDisplacement64(targetAddress);
			std::string errorMessage;
			encoder->TryEncode(instruction, IP, _, errorMessage);
			bool b = instruction.GetIPRelativeMemoryAddress() == (instruction.GetMemoryBase() == Register::EIP ? static_cast<std::uint32_t>(targetAddress) : targetAddress);
			assert(b);
			if (!b)
			{
				errorMessage = "Invalid IP relative address";
			}
			if (errorMessage != "")
			{
				constantOffsets = Iced::Intel::ConstantOffsets();
				return CreateErrorMessage(errorMessage, instruction);
			}
			constantOffsets = encoder->GetConstantOffsets();
			return "";
		}
		case InstrKind::Long:
			isOriginalInstruction = false;
			constantOffsets = Iced::Intel::ConstantOffsets();
			return "IP relative memory operand is too far away and isn't currently supported. " + "Try to allocate memory close to the original instruction (+/-2GB).";
		case InstrKind::Uninitialized:
		default:
			throw InvalidOperationException();
		}
	}
}
