// C# helper headers




// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "SimpleBranchInstr.h"
#include "../OpKind.g.h"
#include "../../NRT_Helpers.h"

namespace Iced::Intel::BlockEncoderInternal
{

	SimpleBranchInstr::SimpleBranchInstr(BlockEncoder* blockEncoder, std::shared_ptr<class Block> block, const Instruction& instruction) : Instr(block, instruction.GetIP())
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
			instrCopy.SetNearBranch64(0);
			shortInstructionSize = blockEncoder->GetInstructionSize(instrCopy, 0);
			nativeCode = ToNativeBranchCode(instruction.GetCode(), blockEncoder->GetBitness());
			if (nativeCode == instruction.GetCode())
			{
				nativeInstructionSize = shortInstructionSize;
			}
			else
			{
				instrCopy = instruction;
				instrCopy.InternalSetCodeNoCheck(nativeCode);
				instrCopy.SetNearBranch64(0);
				nativeInstructionSize = blockEncoder->GetInstructionSize(instrCopy, 0);
			}
			auto switchTempVar_0 = blockEncoder->GetBitness();


			//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
			//ORIGINAL LINE: nearInstructionSize = (switchTempVar_0 == 16) ? nativeInstructionSize + 2 + 3 : (switchTempVar_0 == 32 || switchTempVar_0 == 64) ? nativeInstructionSize + 2 + 5 : throw new InvalidOperationException();
			nearInstructionSize = (switchTempVar_0 == 16) ? nativeInstructionSize + 2 + 3 : (switchTempVar_0 == 32 || switchTempVar_0 == 64) ? nativeInstructionSize + 2 + 5 : throw std::runtime_error("invalid operation");
			if (blockEncoder->GetBitness() == 64)
			{
				longInstructionSize = nativeInstructionSize + 2 + CallOrJmpPointerDataInstructionSize64;
				Size = std::max(std::max(shortInstructionSize, nearInstructionSize), longInstructionSize);
			}
			else
			{
				Size = std::max(shortInstructionSize, nearInstructionSize);
			}
		}
	}

	Iced::Intel::Code SimpleBranchInstr::ToNativeBranchCode(Code code, std::int32_t bitness)
	{
		Code c16, c32, c64;
		switch (code)
		{
		case Code::Loopne_rel8_16_CX:
		case Code::Loopne_rel8_32_CX:
			c16 = Code::Loopne_rel8_16_CX;
			c32 = Code::Loopne_rel8_32_CX;
			c64 = Code::INVALID;
			break;
		case Code::Loopne_rel8_16_ECX:
		case Code::Loopne_rel8_32_ECX:
		case Code::Loopne_rel8_64_ECX:
			c16 = Code::Loopne_rel8_16_ECX;
			c32 = Code::Loopne_rel8_32_ECX;
			c64 = Code::Loopne_rel8_64_ECX;
			break;
		case Code::Loopne_rel8_16_RCX:
		case Code::Loopne_rel8_64_RCX:
			c16 = Code::Loopne_rel8_16_RCX;
			c32 = Code::INVALID;
			c64 = Code::Loopne_rel8_64_RCX;
			break;
		case Code::Loope_rel8_16_CX:
		case Code::Loope_rel8_32_CX:
			c16 = Code::Loope_rel8_16_CX;
			c32 = Code::Loope_rel8_32_CX;
			c64 = Code::INVALID;
			break;
		case Code::Loope_rel8_16_ECX:
		case Code::Loope_rel8_32_ECX:
		case Code::Loope_rel8_64_ECX:
			c16 = Code::Loope_rel8_16_ECX;
			c32 = Code::Loope_rel8_32_ECX;
			c64 = Code::Loope_rel8_64_ECX;
			break;
		case Code::Loope_rel8_16_RCX:
		case Code::Loope_rel8_64_RCX:
			c16 = Code::Loope_rel8_16_RCX;
			c32 = Code::INVALID;
			c64 = Code::Loope_rel8_64_RCX;
			break;
		case Code::Loop_rel8_16_CX:
		case Code::Loop_rel8_32_CX:
			c16 = Code::Loop_rel8_16_CX;
			c32 = Code::Loop_rel8_32_CX;
			c64 = Code::INVALID;
			break;
		case Code::Loop_rel8_16_ECX:
		case Code::Loop_rel8_32_ECX:
		case Code::Loop_rel8_64_ECX:
			c16 = Code::Loop_rel8_16_ECX;
			c32 = Code::Loop_rel8_32_ECX;
			c64 = Code::Loop_rel8_64_ECX;
			break;
		case Code::Loop_rel8_16_RCX:
		case Code::Loop_rel8_64_RCX:
			c16 = Code::Loop_rel8_16_RCX;
			c32 = Code::INVALID;
			c64 = Code::Loop_rel8_64_RCX;
			break;
		case Code::Jcxz_rel8_16:
		case Code::Jcxz_rel8_32:
			c16 = Code::Jcxz_rel8_16;
			c32 = Code::Jcxz_rel8_32;
			c64 = Code::INVALID;
			break;
		case Code::Jecxz_rel8_16:
		case Code::Jecxz_rel8_32:
		case Code::Jecxz_rel8_64:
			c16 = Code::Jecxz_rel8_16;
			c32 = Code::Jecxz_rel8_32;
			c64 = Code::Jecxz_rel8_64;
			break;
		case Code::Jrcxz_rel8_16:
		case Code::Jrcxz_rel8_64:
			c16 = Code::Jrcxz_rel8_16;
			c32 = Code::INVALID;
			c64 = Code::Jrcxz_rel8_64;
			break;
		default:
			throw std::out_of_range("code");
		}
		auto switchTempVar_1 = bitness;


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: return (switchTempVar_1 == 16) ? c16 : (switchTempVar_1 == 32) ? c32 : (switchTempVar_1 == 64) ? c64 : throw new ArgumentOutOfRangeException(nameof(bitness));
		return (switchTempVar_1 == 16) ? c16 : (switchTempVar_1 == 32) ? c32 : (switchTempVar_1 == 64) ? c64 : throw std::out_of_range("bitness");
	}

	void SimpleBranchInstr::Initialize(BlockEncoder* blockEncoder)
	{
		targetInstr = blockEncoder->GetTarget(instruction.GetNearBranchTarget());
		TryOptimize(0);
	}

	bool SimpleBranchInstr::Optimize(std::uint64_t gained)
	{
		return TryOptimize(gained);
	}

	bool SimpleBranchInstr::TryOptimize(std::uint64_t gained)
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
	std::string SimpleBranchInstr::TryEncode(Encoder& encoder, ConstantOffsets& constantOffsets, bool& isOriginalInstruction)
	{
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: string? errorMessage;
		std::string errorMessage;
		Instruction instr;
		std::uint32_t size;
		std::uint32_t instrLen;
		switch (instrKind)
		{
		case InstrKind::Unchanged:
		case InstrKind::Short:
			isOriginalInstruction = true;
			instruction.SetNearBranch64(targetInstr.GetAddress());
			std::uint32_t _;
			if (!encoder.TryEncode(instruction, IP, _, errorMessage))
			{
				constantOffsets = Iced::Intel::ConstantOffsets();
				return CreateErrorMessage(errorMessage, instruction);
			}
			constantOffsets = encoder.GetConstantOffsets();
			return "";
		case InstrKind::Near:
		{
			isOriginalInstruction = false;
			constantOffsets = Iced::Intel::ConstantOffsets();
			// Code:
			//		brins tmp		; nativeInstructionSize
			//		jmp short skip	; 2
			//	tmp:
			//		jmp near target	; 3/5/5
			//	skip:
			instr = instruction;
			instr.InternalSetCodeNoCheck(nativeCode);
			instr.SetNearBranch64(IP + nativeInstructionSize + 2);
			if (!encoder.TryEncode(instr, IP, size, errorMessage))
			{
				return CreateErrorMessage(errorMessage, instruction);
			}
			instr = Instruction();
			instr.SetNearBranch64(IP + nearInstructionSize);
			Code codeNear;
			switch (encoder.GetBitness())
			{
			case 16:
				instr.InternalSetCodeNoCheck(Code::Jmp_rel8_16);
				codeNear = Code::Jmp_rel16;
				instr.SetOp0Kind(OpKind::NearBranch16);
				break;
			case 32:
				instr.InternalSetCodeNoCheck(Code::Jmp_rel8_32);
				codeNear = Code::Jmp_rel32_32;
				instr.SetOp0Kind(OpKind::NearBranch32);
				break;
			case 64:
				instr.InternalSetCodeNoCheck(Code::Jmp_rel8_64);
				codeNear = Code::Jmp_rel32_64;
				instr.SetOp0Kind(OpKind::NearBranch64);
				break;
			default:
				throw std::runtime_error("invalid operation");
			}
			if (!encoder.TryEncode(instr, IP + size, instrLen, errorMessage))
			{
				return CreateErrorMessage(errorMessage, instruction);
			}
			size += instrLen;
			instr.InternalSetCodeNoCheck(codeNear);
			instr.SetNearBranch64(targetInstr.GetAddress());
			encoder.TryEncode(instr, IP + size, instrLen, errorMessage);
			if (errorMessage != "")
			{
				return CreateErrorMessage(errorMessage, instruction);
			}
			return "";
		}
		case InstrKind::Long:
			assert(encoder.GetBitness() == 64);
			System::Diagnostics::Debug2::Assert(pointerData != nullptr);
			isOriginalInstruction = false;
			constantOffsets = Iced::Intel::ConstantOffsets();
			pointerData->Data = targetInstr.GetAddress();
			// Code:
			//		brins tmp		; nativeInstructionSize
			//		jmp short skip	; 2
			//	tmp:
			//		jmp [mem_loc]	; 6
			//	skip:
			instr = instruction;
			instr.InternalSetCodeNoCheck(nativeCode);
			instr.SetNearBranch64(IP + nativeInstructionSize + 2);
			if (!encoder.TryEncode(instr, IP, instrLen, errorMessage))
			{
				return CreateErrorMessage(errorMessage, instruction);
			}
			size = instrLen;
			instr = Instruction();
			instr.SetNearBranch64(IP + longInstructionSize);
			switch (encoder.GetBitness())
			{
			case 16:
				instr.InternalSetCodeNoCheck(Code::Jmp_rel8_16);
				instr.SetOp0Kind(OpKind::NearBranch16);
				break;
			case 32:
				instr.InternalSetCodeNoCheck(Code::Jmp_rel8_32);
				instr.SetOp0Kind(OpKind::NearBranch32);
				break;
			case 64:
				instr.InternalSetCodeNoCheck(Code::Jmp_rel8_64);
				instr.SetOp0Kind(OpKind::NearBranch64);
				break;
			default:
				throw std::runtime_error("invalid operation");
			}
			if (!encoder.TryEncode(instr, IP + size, instrLen, errorMessage))
			{
				return CreateErrorMessage(errorMessage, instruction);
			}
			size += instrLen;
			errorMessage = EncodeBranchToPointerData(encoder, false, IP + size, pointerData, _, Size - size);
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
