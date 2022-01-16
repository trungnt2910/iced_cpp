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

#include "OpCodeFormatter.h"
#include "../Code.g.h"
#include "../EncodingKind.g.h"
#include "../OpCodeTableKind.g.h"
#include "../MandatoryPrefix.g.h"
#include "../MvexInfo.h"
#include "../MvexEHBit.g.h"

namespace Iced::Intel::EncoderInternal
{

	OpCodeFormatter::OpCodeFormatter(OpCodeInfo* opCode, StringBuilder* sb, LKind lkind, bool hasModrmInfo)
	{
		this->opCode = opCode;
		this->sb = sb;
		this->lkind = lkind;
		this->hasModrmInfo = hasModrmInfo;
	}

	std::string OpCodeFormatter::Format()
	{
		if (!opCode->IsInstruction())
		{
			auto switchTempVar_0 = opCode->GetCode();
			// GENERATOR-BEGIN: OpCodeFmtNotInstructionString
			// ⚠️This was generated by GENERATOR!🦹‍♂️
			// GENERATOR-END: OpCodeFmtNotInstructionString

	 //C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
	 //ORIGINAL LINE: return (switchTempVar_0 == Code.INVALID) ? "<invalid>" : (switchTempVar_0 == Code.DeclareByte) ? "<db>" : (switchTempVar_0 == Code.DeclareWord) ? "<dw>" : (switchTempVar_0 == Code.DeclareDword) ? "<dd>" : (switchTempVar_0 == Code.DeclareQword) ? "<dq>" : throw new InvalidOperationException();
			return (switchTempVar_0 == Code::INVALID) ? "<invalid>" : (switchTempVar_0 == Code::DeclareByte) ? "<db>" : (switchTempVar_0 == Code::DeclareWord) ? "<dw>" : (switchTempVar_0 == Code::DeclareDword) ? "<dd>" : (switchTempVar_0 == Code::DeclareQword) ? "<dq>" : throw InvalidOperationException();
		}
		auto switchTempVar_1 = opCode->GetEncoding();


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: return (switchTempVar_1 == EncodingKind.Legacy) ? Format_Legacy() : (switchTempVar_1 == EncodingKind.VEX) ? FormatVecEncoding("VEX") : (switchTempVar_1 == EncodingKind.EVEX) ? FormatVecEncoding("EVEX") : (switchTempVar_1 == EncodingKind.XOP) ? FormatVecEncoding("XOP") : (switchTempVar_1 == EncodingKind.D3NOW) ? Format_3DNow() : (switchTempVar_1 == EncodingKind.MVEX) ? FormatVecEncoding("MVEX") : throw new InvalidOperationException();
		return (switchTempVar_1 == EncodingKind::Legacy) ? Format_Legacy() : (switchTempVar_1 == EncodingKind::VEX) ? FormatVecEncoding("VEX") : (switchTempVar_1 == EncodingKind::EVEX) ? FormatVecEncoding("EVEX") : (switchTempVar_1 == EncodingKind::XOP) ? FormatVecEncoding("XOP") : (switchTempVar_1 == EncodingKind::D3NOW) ? Format_3DNow() : (switchTempVar_1 == EncodingKind::MVEX) ? FormatVecEncoding("MVEX") : throw InvalidOperationException();
	}

	void OpCodeFormatter::AppendHexByte(std::uint8_t value)
	{
		//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
		sb->append(value.ToString("X2"));
	}

	void OpCodeFormatter::AppendOpCode(std::uint32_t value, std::int32_t valueLen, bool sep)
	{
		if (valueLen == 1)
		{
			AppendHexByte(static_cast<std::uint8_t>(value));
		}
		else
		{
			assert(valueLen == 2);
			AppendHexByte(static_cast<std::uint8_t>(value >> 8));
			if (sep)
			{
				sb->append(' ');
			}
			AppendHexByte(static_cast<std::uint8_t>(value));
		}
	}

	void OpCodeFormatter::AppendTable(bool sep)
	{
		switch (opCode->GetTable())
		{
		case OpCodeTableKind::Normal:
			break;
		case OpCodeTableKind::T0F:
			AppendOpCode(0x0F, 1, sep);
			break;
		case OpCodeTableKind::T0F38:
			AppendOpCode(0x0F38, 2, sep);
			break;
		case OpCodeTableKind::T0F3A:
			AppendOpCode(0x0F3A, 2, sep);
			break;
		case OpCodeTableKind::MAP5:
			sb->append("MAP5");
			break;
		case OpCodeTableKind::MAP6:
			sb->append("MAP6");
			break;
		case OpCodeTableKind::MAP8:
			sb->append("X8");
			break;
		case OpCodeTableKind::MAP9:
			sb->append("X9");
			break;
		case OpCodeTableKind::MAP10:
			sb->append("XA");
			break;
		default:
			throw InvalidOperationException();
		}
	}

	bool OpCodeFormatter::HasModRM()
	{
		std::int32_t opCount = opCode->GetOpCount();
		if (opCount == 0)
		{
			return false;
		}
		switch (opCode->GetEncoding())
		{
		case EncodingKind::Legacy:
		case EncodingKind::VEX:
			break;
		case EncodingKind::EVEX:
		case EncodingKind::XOP:
		case EncodingKind::D3NOW:
		case EncodingKind::MVEX:
			return true;
		default:
			throw InvalidOperationException();
		}
		for (std::int32_t i = 0; i < opCount; i++)
		{
			switch (opCode->GetOpKind(i))
			{
				// GENERATOR-BEGIN: HasModRM
				// ⚠️This was generated by GENERATOR!🦹‍♂️
			case OpCodeOperandKind::mem:
			case OpCodeOperandKind::mem_mpx:
			case OpCodeOperandKind::mem_mib:
			case OpCodeOperandKind::mem_vsib32x:
			case OpCodeOperandKind::mem_vsib64x:
			case OpCodeOperandKind::mem_vsib32y:
			case OpCodeOperandKind::mem_vsib64y:
			case OpCodeOperandKind::mem_vsib32z:
			case OpCodeOperandKind::mem_vsib64z:
			case OpCodeOperandKind::r8_or_mem:
			case OpCodeOperandKind::r16_or_mem:
			case OpCodeOperandKind::r32_or_mem:
			case OpCodeOperandKind::r32_or_mem_mpx:
			case OpCodeOperandKind::r64_or_mem:
			case OpCodeOperandKind::r64_or_mem_mpx:
			case OpCodeOperandKind::mm_or_mem:
			case OpCodeOperandKind::xmm_or_mem:
			case OpCodeOperandKind::ymm_or_mem:
			case OpCodeOperandKind::zmm_or_mem:
			case OpCodeOperandKind::bnd_or_mem_mpx:
			case OpCodeOperandKind::k_or_mem:
			case OpCodeOperandKind::r8_reg:
			case OpCodeOperandKind::r16_reg:
			case OpCodeOperandKind::r16_reg_mem:
			case OpCodeOperandKind::r16_rm:
			case OpCodeOperandKind::r32_reg:
			case OpCodeOperandKind::r32_reg_mem:
			case OpCodeOperandKind::r32_rm:
			case OpCodeOperandKind::r64_reg:
			case OpCodeOperandKind::r64_reg_mem:
			case OpCodeOperandKind::r64_rm:
			case OpCodeOperandKind::seg_reg:
			case OpCodeOperandKind::k_reg:
			case OpCodeOperandKind::kp1_reg:
			case OpCodeOperandKind::k_rm:
			case OpCodeOperandKind::mm_reg:
			case OpCodeOperandKind::mm_rm:
			case OpCodeOperandKind::xmm_reg:
			case OpCodeOperandKind::xmm_rm:
			case OpCodeOperandKind::ymm_reg:
			case OpCodeOperandKind::ymm_rm:
			case OpCodeOperandKind::zmm_reg:
			case OpCodeOperandKind::zmm_rm:
			case OpCodeOperandKind::cr_reg:
			case OpCodeOperandKind::dr_reg:
			case OpCodeOperandKind::tr_reg:
			case OpCodeOperandKind::bnd_reg:
			case OpCodeOperandKind::sibmem:
			case OpCodeOperandKind::tmm_reg:
			case OpCodeOperandKind::tmm_rm:
				return true;
				// GENERATOR-END: HasModRM
			default:
				break;
			}
		}
		return false;
	}

	bool OpCodeFormatter::HasVsib()
	{
		std::int32_t opCount = opCode->GetOpCount();
		for (std::int32_t i = 0; i < opCount; i++)
		{
			switch (opCode->GetOpKind(i))
			{
				// GENERATOR-BEGIN: HasVsib
				// ⚠️This was generated by GENERATOR!🦹‍♂️
			case OpCodeOperandKind::mem_vsib32x:
			case OpCodeOperandKind::mem_vsib64x:
			case OpCodeOperandKind::mem_vsib32y:
			case OpCodeOperandKind::mem_vsib64y:
			case OpCodeOperandKind::mem_vsib32z:
			case OpCodeOperandKind::mem_vsib64z:
				return true;
				// GENERATOR-END: HasVsib
			default:
				break;
			}
		}
		return false;
	}

	Iced::Intel::OpCodeOperandKind OpCodeFormatter::GetOpCodeBitsOperand()
	{
		std::int32_t opCount = opCode->GetOpCount();
		for (std::int32_t i = 0; i < opCount; i++)
		{
			auto opKind = opCode->GetOpKind(i);
			switch (opKind)
			{
			case OpCodeOperandKind::r8_opcode:
			case OpCodeOperandKind::r16_opcode:
			case OpCodeOperandKind::r32_opcode:
			case OpCodeOperandKind::r64_opcode:
				return opKind;
			}
		}
		return OpCodeOperandKind::None;
	}

	bool OpCodeFormatter::TryGetModrmInfo(bool& isRegOnly, std::int32_t& rrr, std::int32_t& bbb)
	{
		isRegOnly = true;
		rrr = opCode->GetGroupIndex();
		bbb = opCode->GetRmGroupIndex();
		if (!hasModrmInfo)
		{
			return false;
		}
		std::int32_t opCount = opCode->GetOpCount();
		for (std::int32_t i = 0; i < opCount; i++)
		{
			switch (opCode->GetOpKind(i))
			{
			case OpCodeOperandKind::mem_offs:
			case OpCodeOperandKind::mem:
			case OpCodeOperandKind::mem_mpx:
			case OpCodeOperandKind::mem_mib:
				isRegOnly = false;
				break;
			case OpCodeOperandKind::mem_vsib32x:
			case OpCodeOperandKind::mem_vsib64x:
			case OpCodeOperandKind::mem_vsib32y:
			case OpCodeOperandKind::mem_vsib64y:
			case OpCodeOperandKind::mem_vsib32z:
			case OpCodeOperandKind::mem_vsib64z:
			case OpCodeOperandKind::sibmem:
				isRegOnly = false;
				bbb = 4;
				break;
			}
		}
		return true;
	}

	void OpCodeFormatter::AppendBits(const std::string& name, std::int32_t bits, std::int32_t numBits)
	{
		if (bits < 0)
		{
			sb->append(name);
		}
		else
		{
			for (std::int32_t i = numBits - 1; i >= 0; i--)
			{
				if (((bits >> i) & 1) != 0)
				{
					sb->append('1');
				}
				else
				{
					sb->append('0');
				}
			}
		}
	}

	void OpCodeFormatter::AppendRest()
	{
		bool isRegOnly;
		std::int32_t rrr;
		std::int32_t bbb;
		if (TryGetModrmInfo(isRegOnly, rrr, bbb))
		{
			if (isRegOnly)
			{
				sb->append(" 11:");
			}
			else
			{
				sb->append(" !(11):");
			}
			AppendBits("rrr", rrr, 3);
			sb->append(':');
			AppendBits("bbb", bbb, 3);
		}
		else
		{
			bool isVsib = (opCode->GetEncoding() == EncodingKind::EVEX || opCode->GetEncoding() == EncodingKind::MVEX) && HasVsib();
			if (opCode->IsGroup())
			{
				sb->append(" /");
				sb->append(opCode->GetGroupIndex());
			}
			else if (!isVsib && HasModRM())
			{
				sb->append(" /r");
			}
			if (isVsib)
			{
				sb->append(" /vsib");
			}
		}
		std::int32_t opCount = opCode->GetOpCount();
		for (std::int32_t i = 0; i < opCount; i++)
		{
			switch (opCode->GetOpKind(i))
			{
			case OpCodeOperandKind::br16_1:
			case OpCodeOperandKind::br32_1:
			case OpCodeOperandKind::br64_1:
				sb->append(" cb");
				break;
			case OpCodeOperandKind::br16_2:
			case OpCodeOperandKind::xbegin_2:
			case OpCodeOperandKind::brdisp_2:
				sb->append(" cw");
				break;
			case OpCodeOperandKind::farbr2_2:
			case OpCodeOperandKind::br32_4:
			case OpCodeOperandKind::br64_4:
			case OpCodeOperandKind::xbegin_4:
			case OpCodeOperandKind::brdisp_4:
				sb->append(" cd");
				break;
			case OpCodeOperandKind::farbr4_2:
				sb->append(" cp");
				break;
			case OpCodeOperandKind::imm8:
			case OpCodeOperandKind::imm8sex16:
			case OpCodeOperandKind::imm8sex32:
			case OpCodeOperandKind::imm8sex64:
				sb->append(" ib");
				break;
			case OpCodeOperandKind::imm16:
				sb->append(" iw");
				break;
			case OpCodeOperandKind::imm32:
			case OpCodeOperandKind::imm32sex64:
				sb->append(" id");
				break;
			case OpCodeOperandKind::imm64:
				sb->append(" io");
				break;
			case OpCodeOperandKind::xmm_is4:
			case OpCodeOperandKind::ymm_is4:
				sb->append(" /is4");
				break;
			case OpCodeOperandKind::xmm_is5:
			case OpCodeOperandKind::ymm_is5:
				sb->append(" /is5");
				// don't show the next imm8
				i = opCount;
				break;
			case OpCodeOperandKind::mem_offs:
				sb->append(" mo");
				break;
			}
		}
	}

	std::string OpCodeFormatter::Format_Legacy()
	{
		sb->setLength(0);
		if (opCode->GetFwait())
		{
			AppendHexByte(0x9B);
			sb->append(' ');
		}
		switch (opCode->GetAddressSize())
		{
		case 0:
			break;
		case 16:
			sb->append("a16 ");
			break;
		case 32:
			sb->append("a32 ");
			break;
		case 64:
			sb->append("a64 ");
			break;
		default:
			throw InvalidOperationException();
		}
		switch (opCode->GetOperandSize())
		{
		case 0:
			break;
		case 16:
			sb->append("o16 ");
			break;
		case 32:
			sb->append("o32 ");
			break;
		case 64:
			// o64 (REX.W) must be immediately before the opcode and is handled below
			break;
		default:
			throw InvalidOperationException();
		}
		switch (opCode->GetMandatoryPrefix())
		{
		case MandatoryPrefix::None:
			break;
		case MandatoryPrefix::PNP:
			sb->append("NP ");
			break;
		case MandatoryPrefix::P66:
			AppendHexByte(0x66);
			sb->append(' ');
			break;
		case MandatoryPrefix::PF3:
			AppendHexByte(0xF3);
			sb->append(' ');
			break;
		case MandatoryPrefix::PF2:
			AppendHexByte(0xF2);
			sb->append(' ');
			break;
		default:
			throw InvalidOperationException();
		}
		if (opCode->GetOperandSize() == 64)
		{
			sb->append("o64 ");
		}
		AppendTable(true);
		if (opCode->GetTable() != OpCodeTableKind::Normal)
		{
			sb->append(' ');
		}
		AppendOpCode(opCode->GetOpCode(), opCode->GetOpCodeLength(), true);
		switch (GetOpCodeBitsOperand())
		{
		case OpCodeOperandKind::r8_opcode:
			sb->append("+rb");
			break;
		case OpCodeOperandKind::r16_opcode:
			sb->append("+rw");
			break;
		case OpCodeOperandKind::r32_opcode:
			sb->append("+rd");
			break;
		case OpCodeOperandKind::r64_opcode:
			sb->append("+ro");
			break;
		case OpCodeOperandKind::None:
			break;
		default:
			throw InvalidOperationException();
		}
		std::int32_t opCount = opCode->GetOpCount();
		for (std::int32_t i = 0; i < opCount; i++)
		{
			if (opCode->GetOpKind(i) == OpCodeOperandKind::sti_opcode)
			{
				sb->append("+i");
				break;
			}
		}
		AppendRest();
		return sb->toString();
	}

	std::string OpCodeFormatter::Format_3DNow()
	{
		sb->setLength(0);
		AppendOpCode(0x0F0F, 2, true);
		sb->append(" /r");
		sb->append(' ');
		AppendOpCode(opCode->GetOpCode(), opCode->GetOpCodeLength(), true);
		return sb->toString();
	}

	std::string OpCodeFormatter::FormatVecEncoding(const std::string& encodingName)
	{
		sb->setLength(0);
		sb->append(encodingName);
		if (opCode->GetEncoding() == EncodingKind::MVEX)
		{
			auto mvexInfo = MvexInfo(opCode->GetCode());
			if (mvexInfo.IsNDD())
			{
				sb->append(".NDD");
			}
			else if (mvexInfo.IsNDS())
			{
				sb->append(".NDS");
			}
		}
		sb->append('.');
		if (opCode->IsLIG())
		{
			sb->append("LIG");
		}
		else
		{
			switch (lkind)
			{
			case LKind::L128:
				sb->append(128U << static_cast<std::int32_t>(opCode->GetL()));
				break;
			case LKind::L0:
				sb->append('L');
				sb->append(opCode->GetL());
				break;
			case LKind::LZ:
				if (opCode->GetL() != 0)
				{
					throw InvalidOperationException();
				}
				sb->append("LZ");
				break;
			case LKind::None:
			default:
				throw InvalidOperationException();
			}
		}
		switch (opCode->GetMandatoryPrefix())
		{
		case MandatoryPrefix::None:
		case MandatoryPrefix::PNP:
			break;
		case MandatoryPrefix::P66:
			sb->append('.');
			AppendHexByte(0x66);
			break;
		case MandatoryPrefix::PF3:
			sb->append('.');
			AppendHexByte(0xF3);
			break;
		case MandatoryPrefix::PF2:
			sb->append('.');
			AppendHexByte(0xF2);
			break;
		default:
			throw InvalidOperationException();
		}
		if (opCode->GetTable() != OpCodeTableKind::Normal)
		{
			sb->append('.');
		}
		AppendTable(false);
		if (opCode->IsWIG())
		{
			sb->append(".WIG");
		}
		else
		{
			sb->append(".W");
			sb->append(opCode->GetW());
		}
		if (opCode->GetEncoding() == EncodingKind::MVEX)
		{
			auto mvexInfo = MvexInfo(opCode->GetCode());
			switch (mvexInfo.GetEHBit())
			{
			case MvexEHBit::None:
				break;
			case MvexEHBit::EH0:
				sb->append(".EH0");
				break;
			case MvexEHBit::EH1:
				sb->append(".EH1");
				break;
			default:
				throw InvalidOperationException();
			}
		}
		sb->append(' ');
		AppendOpCode(opCode->GetOpCode(), opCode->GetOpCodeLength(), true);
		AppendRest();
		return sb->toString();
	}
}
