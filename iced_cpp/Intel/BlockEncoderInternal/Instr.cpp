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

#include "Instr.h"
#include "../Code.g.h"
#include "JccInstr.h"
#include "SimpleBranchInstr.h"
#include "CallInstr.h"
#include "JmpInstr.h"
#include "XbeginInstr.h"
#include "../OpKind.g.h"
#include "IpRelMemOpInstr.h"
#include "SimpleInstr.h"
#include "../Register.g.h"

namespace Iced::Intel::BlockEncoderInternal
{

	Instr::Instr(std::shared_ptr<class Block> block, std::uint64_t origIp)
	{
		OrigIP = origIp;
		Block = block;
	}

	std::string Instr::CreateErrorMessage(const std::string& errorMessage, const Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
		return std::format("{0:s} : 0x{1:0>X} {2:s}", errorMessage, instruction.GetIP(), to_string(instruction));
	}

	std::shared_ptr<Instr> Instr::Create(BlockEncoder* blockEncoder, std::shared_ptr<class Block> block, const Instruction& instruction)
	{
		switch (instruction.GetCode())
		{
			// GENERATOR-BEGIN: JccInstr
			// ⚠️This was generated by GENERATOR!🦹‍♂️
		case Code::Jo_rel8_16:
		case Code::Jo_rel8_32:
		case Code::Jo_rel8_64:
		case Code::Jno_rel8_16:
		case Code::Jno_rel8_32:
		case Code::Jno_rel8_64:
		case Code::Jb_rel8_16:
		case Code::Jb_rel8_32:
		case Code::Jb_rel8_64:
		case Code::Jae_rel8_16:
		case Code::Jae_rel8_32:
		case Code::Jae_rel8_64:
		case Code::Je_rel8_16:
		case Code::Je_rel8_32:
		case Code::Je_rel8_64:
		case Code::Jne_rel8_16:
		case Code::Jne_rel8_32:
		case Code::Jne_rel8_64:
		case Code::Jbe_rel8_16:
		case Code::Jbe_rel8_32:
		case Code::Jbe_rel8_64:
		case Code::Ja_rel8_16:
		case Code::Ja_rel8_32:
		case Code::Ja_rel8_64:
		case Code::Js_rel8_16:
		case Code::Js_rel8_32:
		case Code::Js_rel8_64:
		case Code::Jns_rel8_16:
		case Code::Jns_rel8_32:
		case Code::Jns_rel8_64:
		case Code::Jp_rel8_16:
		case Code::Jp_rel8_32:
		case Code::Jp_rel8_64:
		case Code::Jnp_rel8_16:
		case Code::Jnp_rel8_32:
		case Code::Jnp_rel8_64:
		case Code::Jl_rel8_16:
		case Code::Jl_rel8_32:
		case Code::Jl_rel8_64:
		case Code::Jge_rel8_16:
		case Code::Jge_rel8_32:
		case Code::Jge_rel8_64:
		case Code::Jle_rel8_16:
		case Code::Jle_rel8_32:
		case Code::Jle_rel8_64:
		case Code::Jg_rel8_16:
		case Code::Jg_rel8_32:
		case Code::Jg_rel8_64:
		case Code::Jo_rel16:
		case Code::Jo_rel32_32:
		case Code::Jo_rel32_64:
		case Code::Jno_rel16:
		case Code::Jno_rel32_32:
		case Code::Jno_rel32_64:
		case Code::Jb_rel16:
		case Code::Jb_rel32_32:
		case Code::Jb_rel32_64:
		case Code::Jae_rel16:
		case Code::Jae_rel32_32:
		case Code::Jae_rel32_64:
		case Code::Je_rel16:
		case Code::Je_rel32_32:
		case Code::Je_rel32_64:
		case Code::Jne_rel16:
		case Code::Jne_rel32_32:
		case Code::Jne_rel32_64:
		case Code::Jbe_rel16:
		case Code::Jbe_rel32_32:
		case Code::Jbe_rel32_64:
		case Code::Ja_rel16:
		case Code::Ja_rel32_32:
		case Code::Ja_rel32_64:
		case Code::Js_rel16:
		case Code::Js_rel32_32:
		case Code::Js_rel32_64:
		case Code::Jns_rel16:
		case Code::Jns_rel32_32:
		case Code::Jns_rel32_64:
		case Code::Jp_rel16:
		case Code::Jp_rel32_32:
		case Code::Jp_rel32_64:
		case Code::Jnp_rel16:
		case Code::Jnp_rel32_32:
		case Code::Jnp_rel32_64:
		case Code::Jl_rel16:
		case Code::Jl_rel32_32:
		case Code::Jl_rel32_64:
		case Code::Jge_rel16:
		case Code::Jge_rel32_32:
		case Code::Jge_rel32_64:
		case Code::Jle_rel16:
		case Code::Jle_rel32_32:
		case Code::Jle_rel32_64:
		case Code::Jg_rel16:
		case Code::Jg_rel32_32:
		case Code::Jg_rel32_64:
		case Code::VEX_KNC_Jkzd_kr_rel8_64:
		case Code::VEX_KNC_Jknzd_kr_rel8_64:
		case Code::VEX_KNC_Jkzd_kr_rel32_64:
		case Code::VEX_KNC_Jknzd_kr_rel32_64:
			return std::make_shared<JccInstr>(blockEncoder, block, instruction);
			// GENERATOR-END: JccInstr
			// GENERATOR-BEGIN: SimpleBranchInstr
			// ⚠️This was generated by GENERATOR!🦹‍♂️
		case Code::Loopne_rel8_16_CX:
		case Code::Loopne_rel8_32_CX:
		case Code::Loopne_rel8_16_ECX:
		case Code::Loopne_rel8_32_ECX:
		case Code::Loopne_rel8_64_ECX:
		case Code::Loopne_rel8_16_RCX:
		case Code::Loopne_rel8_64_RCX:
		case Code::Loope_rel8_16_CX:
		case Code::Loope_rel8_32_CX:
		case Code::Loope_rel8_16_ECX:
		case Code::Loope_rel8_32_ECX:
		case Code::Loope_rel8_64_ECX:
		case Code::Loope_rel8_16_RCX:
		case Code::Loope_rel8_64_RCX:
		case Code::Loop_rel8_16_CX:
		case Code::Loop_rel8_32_CX:
		case Code::Loop_rel8_16_ECX:
		case Code::Loop_rel8_32_ECX:
		case Code::Loop_rel8_64_ECX:
		case Code::Loop_rel8_16_RCX:
		case Code::Loop_rel8_64_RCX:
		case Code::Jcxz_rel8_16:
		case Code::Jcxz_rel8_32:
		case Code::Jecxz_rel8_16:
		case Code::Jecxz_rel8_32:
		case Code::Jecxz_rel8_64:
		case Code::Jrcxz_rel8_16:
		case Code::Jrcxz_rel8_64:
			return std::make_shared<SimpleBranchInstr>(blockEncoder, block, instruction);
			// GENERATOR-END: SimpleBranchInstr
			// GENERATOR-BEGIN: CallInstr
			// ⚠️This was generated by GENERATOR!🦹‍♂️
		case Code::Call_rel16:
		case Code::Call_rel32_32:
		case Code::Call_rel32_64:
			return std::make_shared<CallInstr>(blockEncoder, block, instruction);
			// GENERATOR-END: CallInstr
			// GENERATOR-BEGIN: JmpInstr
			// ⚠️This was generated by GENERATOR!🦹‍♂️
		case Code::Jmp_rel16:
		case Code::Jmp_rel32_32:
		case Code::Jmp_rel32_64:
		case Code::Jmp_rel8_16:
		case Code::Jmp_rel8_32:
		case Code::Jmp_rel8_64:
			return std::make_shared<JmpInstr>(blockEncoder, block, instruction);
			// GENERATOR-END: JmpInstr
			// GENERATOR-BEGIN: XbeginInstr
			// ⚠️This was generated by GENERATOR!🦹‍♂️
		case Code::Xbegin_rel16:
		case Code::Xbegin_rel32:
			return std::make_shared<XbeginInstr>(blockEncoder, block, instruction);
			// GENERATOR-END: XbeginInstr
		default:
			break;
		}
		if (blockEncoder->GetBitness() == 64)
		{
			std::int32_t ops = instruction.GetOpCount();
			for (std::int32_t i = 0; i < ops; i++)
			{
				if (instruction.GetOpKind(i) == OpKind::Memory)
				{
					if (instruction.IsIPRelativeMemoryOperand())
					{
						return std::make_shared<IpRelMemOpInstr>(blockEncoder, block, instruction);
					}
					break;
				}
			}
		}
		return std::make_shared<SimpleInstr>(blockEncoder, block, instruction);
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: protected string? EncodeBranchToPointerData(Encoder encoder, bool isCall, ulong ip, BlockData pointerData, out uint size, uint minSize)
	std::string Instr::EncodeBranchToPointerData(Encoder& encoder, bool isCall, std::uint64_t ip, BlockData* pointerData, std::uint32_t& size, std::uint32_t minSize)
	{
		auto Block = this->Block.lock();
		if (!Block)
		{
			throw std::runtime_error("block has been destroyed.");
		}
		if (minSize > (std::uint32_t)std::numeric_limits<std::int32_t>::max())
		{
			throw ArgumentOutOfRangeException("minSize");
		}
		auto instr = Instruction();
		instr.SetOp0Kind(OpKind::Memory);
		instr.SetMemoryDisplSize(encoder.GetBitness() / 8);
		RelocKind relocKind;
		switch (encoder.GetBitness())
		{
		case 64:
		{
			instr.InternalSetCodeNoCheck(isCall ? Code::Call_rm64 : Code::Jmp_rm64);
			instr.SetMemoryBase(Register::RIP);
			auto nextRip = ip + CallOrJmpPointerDataInstructionSize64;
			std::int64_t diff = static_cast<std::int64_t>(pointerData->GetAddress() - nextRip);
			if (!(std::numeric_limits<std::int32_t>::min() <= diff && diff <= std::numeric_limits<std::int32_t>::max()))
			{
				size = 0;
				return "Block is too big";
			}
			instr.SetMemoryDisplacement64(pointerData->GetAddress());
			relocKind = RelocKind::Offset64;
			break;
		}
		default:
			throw InvalidOperationException();
		}
		std::string errorMessage;
		if (!encoder.TryEncode(instr, ip, size, errorMessage))
		{
			return errorMessage;
		}
		if (Block->GetCanAddRelocInfos() && relocKind != RelocKind::Offset64)
		{
			auto constantOffsets = encoder.GetConstantOffsets();
			if (!constantOffsets.GetHasDisplacement())
			{
				return "Internal error: no displ";
			}
			Block->AddRelocInfo(RelocInfo(relocKind, IP + constantOffsets.DisplacementOffset));
		}
		while (size < minSize)
		{
			size++;
			Block->CodeWriter.WriteByte(0x90);
		}
		return "";
	}

	std::int64_t Instr::CorrectDiff(bool inBlock, std::int64_t diff, std::uint64_t gained)
	{
		if (inBlock && diff >= 0)
		{
			assert(static_cast<std::uint64_t>(diff) >= gained);
			return diff - static_cast<std::int64_t>(gained);
		}
		else
		{
			return diff;
		}
	}
}
