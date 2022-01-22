// C# helper headers
#include <csharp/classes.h>
#include <csharp/enum.h>



// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "JccInstr.h"
#include "../Iced.Intel.InstructionInfoExtensions.h"
#include "../../NRT_Helpers.h"
#include "../OpKind.g.h"

#include "Block.h"

namespace Iced::Intel::BlockEncoderInternal
{
	std::uint32_t JccInstr::GetLongInstructionSize64(const Instruction& instruction)
	{
		// Check if JKZD/JKNZD
		if (instruction.GetOpCount() == 2)
		{
			return 5 + CallOrJmpPointerDataInstructionSize64;
		}
		// Code:
		//		!jcc short skip		; negated jcc opcode
		//		jmp qword ptr [rip+mem]
		//	skip:
		return 2 + CallOrJmpPointerDataInstructionSize64;
	}

	JccInstr::JccInstr(BlockEncoder* blockEncoder, std::shared_ptr<class Block> block, const Instruction& instruction) : Instr(block, instruction.GetIP())
	{
		bitness = blockEncoder->GetBitness();
		this->instruction = instruction;
		instrKind = InstrKind::Uninitialized;
		longInstructionSize64 = GetLongInstructionSize64(instruction);
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
				Size = std::max(nearInstructionSize, longInstructionSize64);
			}
			else
			{
				Size = nearInstructionSize;
			}
		}
	}

	void JccInstr::Initialize(BlockEncoder* blockEncoder)
	{
		targetInstr = blockEncoder->GetTarget(instruction.GetNearBranchTarget());
		TryOptimize(0);
	}

	bool JccInstr::Optimize(std::uint64_t gained)
	{
		return TryOptimize(gained);
	}

	bool JccInstr::TryOptimize(std::uint64_t gained)
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
	std::string JccInstr::TryEncode(Encoder& encoder, ConstantOffsets& constantOffsets, bool& isOriginalInstruction)
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
			uint32_t _;
			if (!encoder.TryEncode(instruction, IP, _, errorMessage))
			{
				constantOffsets = Iced::Intel::ConstantOffsets();
				return CreateErrorMessage(errorMessage, instruction);
			}
			constantOffsets = encoder.GetConstantOffsets();
			return "";
		case InstrKind::Long:
		{
			::System::Diagnostics::Debug2::Assert(pointerData != nullptr);
			isOriginalInstruction = false;
			constantOffsets = Iced::Intel::ConstantOffsets();
			pointerData->Data = targetInstr.GetAddress();
			auto instr = Instruction();
			instr.InternalSetCodeNoCheck(ShortBrToNativeBr(Iced::Intel::InstructionInfoExtensions::ToShortBranch(Iced::Intel::InstructionInfoExtensions::NegateConditionCode(instruction.GetCode())), encoder.GetBitness()));
			if (instruction.GetOpCount() == 1)
			{
				instr.SetOp0Kind(OpKind::NearBranch64);
			}
			else
			{
				assert(instruction.GetOpCount() == 2);
				instr.SetOp0Kind(OpKind::Register);
				instr.SetOp0Register(instruction.GetOp0Register());
				instr.SetOp1Kind(OpKind::NearBranch64);
			}
			assert(encoder.GetBitness() == 64);
			assert(longInstructionSize64 <= (std::uint32_t)std::numeric_limits<std::int8_t>::max());
			instr.SetNearBranch64(IP + longInstructionSize64);
			std::uint32_t instrLen;
			if (!encoder.TryEncode(instr, IP, instrLen, errorMessage))
			{
				return CreateErrorMessage(errorMessage, instruction);
			}
			errorMessage = EncodeBranchToPointerData(encoder, false, IP + static_cast<std::uint32_t>(instrLen), pointerData, _, Size - static_cast<std::uint32_t>(instrLen));
			if (errorMessage != "")
			{
				return CreateErrorMessage(errorMessage, instruction);
			}
			return "";
		}
		case InstrKind::Uninitialized:
		default:
			throw InvalidOperationException();
		}
	}

	Iced::Intel::Code JccInstr::ShortBrToNativeBr(Code code, std::int32_t bitness)
	{
		Code c16, c32, c64;
		switch (code)
		{
		case Code::Jo_rel8_16:
		case Code::Jo_rel8_32:
		case Code::Jo_rel8_64:
			c16 = Code::Jo_rel8_16;
			c32 = Code::Jo_rel8_32;
			c64 = Code::Jo_rel8_64;
			break;
		case Code::Jno_rel8_16:
		case Code::Jno_rel8_32:
		case Code::Jno_rel8_64:
			c16 = Code::Jno_rel8_16;
			c32 = Code::Jno_rel8_32;
			c64 = Code::Jno_rel8_64;
			break;
		case Code::Jb_rel8_16:
		case Code::Jb_rel8_32:
		case Code::Jb_rel8_64:
			c16 = Code::Jb_rel8_16;
			c32 = Code::Jb_rel8_32;
			c64 = Code::Jb_rel8_64;
			break;
		case Code::Jae_rel8_16:
		case Code::Jae_rel8_32:
		case Code::Jae_rel8_64:
			c16 = Code::Jae_rel8_16;
			c32 = Code::Jae_rel8_32;
			c64 = Code::Jae_rel8_64;
			break;
		case Code::Je_rel8_16:
		case Code::Je_rel8_32:
		case Code::Je_rel8_64:
			c16 = Code::Je_rel8_16;
			c32 = Code::Je_rel8_32;
			c64 = Code::Je_rel8_64;
			break;
		case Code::Jne_rel8_16:
		case Code::Jne_rel8_32:
		case Code::Jne_rel8_64:
			c16 = Code::Jne_rel8_16;
			c32 = Code::Jne_rel8_32;
			c64 = Code::Jne_rel8_64;
			break;
		case Code::Jbe_rel8_16:
		case Code::Jbe_rel8_32:
		case Code::Jbe_rel8_64:
			c16 = Code::Jbe_rel8_16;
			c32 = Code::Jbe_rel8_32;
			c64 = Code::Jbe_rel8_64;
			break;
		case Code::Ja_rel8_16:
		case Code::Ja_rel8_32:
		case Code::Ja_rel8_64:
			c16 = Code::Ja_rel8_16;
			c32 = Code::Ja_rel8_32;
			c64 = Code::Ja_rel8_64;
			break;
		case Code::Js_rel8_16:
		case Code::Js_rel8_32:
		case Code::Js_rel8_64:
			c16 = Code::Js_rel8_16;
			c32 = Code::Js_rel8_32;
			c64 = Code::Js_rel8_64;
			break;
		case Code::Jns_rel8_16:
		case Code::Jns_rel8_32:
		case Code::Jns_rel8_64:
			c16 = Code::Jns_rel8_16;
			c32 = Code::Jns_rel8_32;
			c64 = Code::Jns_rel8_64;
			break;
		case Code::Jp_rel8_16:
		case Code::Jp_rel8_32:
		case Code::Jp_rel8_64:
			c16 = Code::Jp_rel8_16;
			c32 = Code::Jp_rel8_32;
			c64 = Code::Jp_rel8_64;
			break;
		case Code::Jnp_rel8_16:
		case Code::Jnp_rel8_32:
		case Code::Jnp_rel8_64:
			c16 = Code::Jnp_rel8_16;
			c32 = Code::Jnp_rel8_32;
			c64 = Code::Jnp_rel8_64;
			break;
		case Code::Jl_rel8_16:
		case Code::Jl_rel8_32:
		case Code::Jl_rel8_64:
			c16 = Code::Jl_rel8_16;
			c32 = Code::Jl_rel8_32;
			c64 = Code::Jl_rel8_64;
			break;
		case Code::Jge_rel8_16:
		case Code::Jge_rel8_32:
		case Code::Jge_rel8_64:
			c16 = Code::Jge_rel8_16;
			c32 = Code::Jge_rel8_32;
			c64 = Code::Jge_rel8_64;
			break;
		case Code::Jle_rel8_16:
		case Code::Jle_rel8_32:
		case Code::Jle_rel8_64:
			c16 = Code::Jle_rel8_16;
			c32 = Code::Jle_rel8_32;
			c64 = Code::Jle_rel8_64;
			break;
		case Code::Jg_rel8_16:
		case Code::Jg_rel8_32:
		case Code::Jg_rel8_64:
			c16 = Code::Jg_rel8_16;
			c32 = Code::Jg_rel8_32;
			c64 = Code::Jg_rel8_64;
			break;
		case Code::VEX_KNC_Jkzd_kr_rel8_64:
		case Code::VEX_KNC_Jknzd_kr_rel8_64:
			if (bitness == 64)
			{
				return code;
			}
			throw InvalidOperationException();
		default:
			throw ArgumentOutOfRangeException("code");
		}
		auto switchTempVar_0 = bitness;


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: return (switchTempVar_0 == 16) ? c16 : (switchTempVar_0 == 32) ? c32 : (switchTempVar_0 == 64) ? c64 : throw new ArgumentOutOfRangeException(nameof(bitness));
		return (switchTempVar_0 == 16) ? c16 : (switchTempVar_0 == 32) ? c32 : (switchTempVar_0 == 64) ? c64 : throw ArgumentOutOfRangeException("bitness");
	}
}
