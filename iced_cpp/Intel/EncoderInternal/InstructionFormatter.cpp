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

#include "InstructionFormatter.h"
#include "../EncodingKind.g.h"
#include "../OpCodeOperandKind.g.h"
#include "../InstructionMemorySizes.g.h"
#include "../MvexInfo.h"
#include "../MvexConvFn.g.h"
#include "../Iced.Intel.MemorySizeExtensions.h"
#include "../MvexEHBit.g.h"

namespace Iced::Intel::EncoderInternal
{
	std::int32_t InstructionFormatter::GetKIndex()
	{
		k_index++;
		if (opMaskIsK1)
		{
			if (k_index == 1)
			{
				return 2;
			}
			if (k_index == 2)
			{
				return 1;
			}
		}
		return k_index;
	}

	std::int32_t InstructionFormatter::GetBndIndex()
	{
		if (bnd_count <= 1)
		{
			return 0;
		}
		bnd_index++;
		return bnd_index;
	}

	std::int32_t InstructionFormatter::GetVecIndex(std::int32_t opIndex)
	{
		if (noVecIndex)
		{
			return 0;
		}
		if (vecIndexSameAsOpIndex)
		{
			return opIndex + 1;
		}
		vec_index++;
		if (swapVecIndex12)
		{
			if (vec_index == 1)
			{
				return 2;
			}
			if (vec_index == 2)
			{
				return 1;
			}
		}
		return vec_index;
	}

	std::int32_t InstructionFormatter::GetTmmIndex()
	{
		tmm_index++;
		return tmm_index;
	}

	InstructionFormatter::InstructionFormatter(OpCodeInfo* opCode, InstrStrFmtOption fmtOption, StringBuilder* sb)
	{
		this->opCode = opCode;
		this->sb = sb;
		noVecIndex = false;
		swapVecIndex12 = false;
		noGprSuffix = false;
		vecIndexSameAsOpIndex = false;
		startOpIndex = 0;
		bnd_count = 0;
		r32_count = 0;
		r64_count = 0;
		r32_index = 0;
		r64_index = 0;
		k_index = 0;
		vec_index = 0;
		tmm_index = 0;
		bnd_index = 0;
		opCount = opCode->GetOpCount();
		opMaskIsK1 = false;
		switch (fmtOption)
		{
		case InstrStrFmtOption::None:
			break;
		case InstrStrFmtOption::OpMaskIsK1_or_NoGprSuffix:
			opMaskIsK1 = true;
			noGprSuffix = true;
			break;
		case InstrStrFmtOption::IncVecIndex:
			vec_index++;
			break;
		case InstrStrFmtOption::NoVecIndex:
			noVecIndex = true;
			break;
		case InstrStrFmtOption::SwapVecIndex12:
			swapVecIndex12 = true;
			break;
		case InstrStrFmtOption::SkipOp0:
			startOpIndex = 1;
			break;
		case InstrStrFmtOption::VecIndexSameAsOpIndex:
			vecIndexSameAsOpIndex = true;
			break;
		default:
			throw InvalidOperationException();
		}
		if ((opCode->GetOp0Kind() == OpCodeOperandKind::k_reg || opCode->GetOp0Kind() == OpCodeOperandKind::kp1_reg) && opCode->GetOpCount() > 2 && opCode->GetEncoding() != EncodingKind::MVEX)
		{
			vecIndexSameAsOpIndex = true;
		}
		for (std::int32_t i = 0; i < opCode->GetOpCount(); i++)
		{
			switch (opCode->GetOpKind(i))
			{
			case OpCodeOperandKind::r32_reg:
			case OpCodeOperandKind::r32_reg_mem:
			case OpCodeOperandKind::r32_rm:
			case OpCodeOperandKind::r32_opcode:
			case OpCodeOperandKind::r32_vvvv:
				r32_count++;
				break;
			case OpCodeOperandKind::r64_reg:
			case OpCodeOperandKind::r64_reg_mem:
			case OpCodeOperandKind::r64_rm:
			case OpCodeOperandKind::r64_opcode:
			case OpCodeOperandKind::r64_vvvv:
				r64_count++;
				break;
			case OpCodeOperandKind::bnd_or_mem_mpx:
			case OpCodeOperandKind::bnd_reg:
				bnd_count++;
				break;
			case OpCodeOperandKind::None:
			case OpCodeOperandKind::farbr2_2:
			case OpCodeOperandKind::farbr4_2:
			case OpCodeOperandKind::mem_offs:
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
			case OpCodeOperandKind::k_or_mem:
			case OpCodeOperandKind::r8_reg:
			case OpCodeOperandKind::r8_opcode:
			case OpCodeOperandKind::r16_reg:
			case OpCodeOperandKind::r16_reg_mem:
			case OpCodeOperandKind::r16_rm:
			case OpCodeOperandKind::r16_opcode:
			case OpCodeOperandKind::seg_reg:
			case OpCodeOperandKind::k_reg:
			case OpCodeOperandKind::kp1_reg:
			case OpCodeOperandKind::k_rm:
			case OpCodeOperandKind::k_vvvv:
			case OpCodeOperandKind::mm_reg:
			case OpCodeOperandKind::mm_rm:
			case OpCodeOperandKind::xmm_reg:
			case OpCodeOperandKind::xmm_rm:
			case OpCodeOperandKind::xmm_vvvv:
			case OpCodeOperandKind::xmmp3_vvvv:
			case OpCodeOperandKind::xmm_is4:
			case OpCodeOperandKind::xmm_is5:
			case OpCodeOperandKind::ymm_reg:
			case OpCodeOperandKind::ymm_rm:
			case OpCodeOperandKind::ymm_vvvv:
			case OpCodeOperandKind::ymm_is4:
			case OpCodeOperandKind::ymm_is5:
			case OpCodeOperandKind::zmm_reg:
			case OpCodeOperandKind::zmm_rm:
			case OpCodeOperandKind::zmm_vvvv:
			case OpCodeOperandKind::zmmp3_vvvv:
			case OpCodeOperandKind::cr_reg:
			case OpCodeOperandKind::dr_reg:
			case OpCodeOperandKind::tr_reg:
			case OpCodeOperandKind::es:
			case OpCodeOperandKind::cs:
			case OpCodeOperandKind::ss:
			case OpCodeOperandKind::ds:
			case OpCodeOperandKind::fs:
			case OpCodeOperandKind::gs:
			case OpCodeOperandKind::al:
			case OpCodeOperandKind::cl:
			case OpCodeOperandKind::ax:
			case OpCodeOperandKind::dx:
			case OpCodeOperandKind::eax:
			case OpCodeOperandKind::rax:
			case OpCodeOperandKind::st0:
			case OpCodeOperandKind::sti_opcode:
			case OpCodeOperandKind::imm4_m2z:
			case OpCodeOperandKind::imm8:
			case OpCodeOperandKind::imm8_const_1:
			case OpCodeOperandKind::imm8sex16:
			case OpCodeOperandKind::imm8sex32:
			case OpCodeOperandKind::imm8sex64:
			case OpCodeOperandKind::imm16:
			case OpCodeOperandKind::imm32:
			case OpCodeOperandKind::imm32sex64:
			case OpCodeOperandKind::imm64:
			case OpCodeOperandKind::seg_rDI:
			case OpCodeOperandKind::br16_1:
			case OpCodeOperandKind::br32_1:
			case OpCodeOperandKind::br64_1:
			case OpCodeOperandKind::br16_2:
			case OpCodeOperandKind::br32_4:
			case OpCodeOperandKind::br64_4:
			case OpCodeOperandKind::xbegin_2:
			case OpCodeOperandKind::xbegin_4:
			case OpCodeOperandKind::brdisp_2:
			case OpCodeOperandKind::brdisp_4:
			case OpCodeOperandKind::sibmem:
			case OpCodeOperandKind::tmm_reg:
			case OpCodeOperandKind::tmm_rm:
			case OpCodeOperandKind::tmm_vvvv:
				break;
			case OpCodeOperandKind::seg_rSI:
			case OpCodeOperandKind::es_rDI:
			case OpCodeOperandKind::seg_rBX_al:
				// string instructions, xlat
				opCount = 0;
				break;
			default:
				throw InvalidOperationException();
			}
		}
	}

	Iced::Intel::MemorySize InstructionFormatter::GetMemorySize(bool isBroadcast)
	{
		std::int32_t index = static_cast<std::int32_t>(opCode->GetCode());
		if (isBroadcast)
		{
			return static_cast<MemorySize>(InstructionMemorySizes::SizesBcst[index]);
		}
		else
		{
			return static_cast<MemorySize>(InstructionMemorySizes::SizesNormal[index]);
		}
	}

	std::string InstructionFormatter::Format()
	{
		if (!opCode->IsInstruction())
		{
			auto switchTempVar_0 = opCode->GetCode();
			// GENERATOR-BEGIN: InstrFmtNotInstructionString
			// ⚠️This was generated by GENERATOR!🦹‍♂️
			// GENERATOR-END: InstrFmtNotInstructionString

	 //C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
	 //ORIGINAL LINE: return (switchTempVar_0 == Code.INVALID) ? "<invalid>" : (switchTempVar_0 == Code.DeclareByte) ? "<db>" : (switchTempVar_0 == Code.DeclareWord) ? "<dw>" : (switchTempVar_0 == Code.DeclareDword) ? "<dd>" : (switchTempVar_0 == Code.DeclareQword) ? "<dq>" : throw new InvalidOperationException();
			return (switchTempVar_0 == Code::INVALID) ? "<invalid>" : (switchTempVar_0 == Code::DeclareByte) ? "<db>" : (switchTempVar_0 == Code::DeclareWord) ? "<dw>" : (switchTempVar_0 == Code::DeclareDword) ? "<dd>" : (switchTempVar_0 == Code::DeclareQword) ? "<dq>" : throw InvalidOperationException();
		}
		sb->setLength(0);
		//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
		Write(to_string(opCode->GetMnemonic()), true);
		if (startOpIndex < opCount)
		{
			sb->append(' ');
			std::int32_t saeErIndex = opCount - 1;
			if (opCode->GetEncoding() != EncodingKind::Legacy && opCode->GetOpKind(saeErIndex) == OpCodeOperandKind::imm8)
			{
				saeErIndex--;
			}
			bool addComma = false;
			for (std::int32_t i = startOpIndex; i < opCount; i++)
			{
				if (addComma)
				{
					WriteOpSeparator();
				}
				addComma = true;
				if (i == saeErIndex && opCode->GetEncoding() == EncodingKind::MVEX)
				{
					auto mvexInfo = MvexInfo(opCode->GetCode());
					auto convFn = mvexInfo.GetConvFn();
					if (convFn != MvexConvFn::None)
					{
						sb->append(ConvFnNames[static_cast<std::int32_t>(convFn) - 1]);
						sb->append('(');
					}
				}
				auto opKind = opCode->GetOpKind(i);
				switch (opKind)
				{
				case OpCodeOperandKind::farbr2_2:
					sb->append("ptr16:16");
					break;
				case OpCodeOperandKind::farbr4_2:
					sb->append("ptr16:32");
					break;
				case OpCodeOperandKind::mem_offs:
					sb->append("moffs");
					WriteMemorySize(GetMemorySize(false));
					break;
				case OpCodeOperandKind::mem:
				case OpCodeOperandKind::mem_mpx:
					WriteMemory();
					break;
				case OpCodeOperandKind::sibmem:
					sb->append("sibmem");
					break;
				case OpCodeOperandKind::mem_mib:
					sb->append("mib");
					break;
				case OpCodeOperandKind::mem_vsib32x:
					sb->append("vm32x");
					break;
				case OpCodeOperandKind::mem_vsib64x:
					sb->append("vm64x");
					break;
				case OpCodeOperandKind::mem_vsib32y:
					sb->append("vm32y");
					break;
				case OpCodeOperandKind::mem_vsib64y:
					sb->append("vm64y");
					break;
				case OpCodeOperandKind::mem_vsib32z:
					if (opCode->GetEncoding() == EncodingKind::MVEX)
					{
						sb->append("mvt");
					}
					else
					{
						sb->append("vm32z");
					}
					break;
				case OpCodeOperandKind::mem_vsib64z:
					sb->append("vm64z");
					break;
				case OpCodeOperandKind::r8_or_mem:
					WriteGprMem(8);
					break;
				case OpCodeOperandKind::r16_or_mem:
					WriteGprMem(16);
					break;
				case OpCodeOperandKind::r32_or_mem:
				case OpCodeOperandKind::r32_or_mem_mpx:
					WriteGprMem(32);
					break;
				case OpCodeOperandKind::r64_or_mem:
				case OpCodeOperandKind::r64_or_mem_mpx:
					WriteGprMem(64);
					break;
				case OpCodeOperandKind::mm_or_mem:
					WriteRegMem("mm", GetVecIndex(i));
					break;
				case OpCodeOperandKind::xmm_or_mem:
					WriteRegMem("xmm", GetVecIndex(i));
					break;
				case OpCodeOperandKind::ymm_or_mem:
					WriteRegMem("ymm", GetVecIndex(i));
					break;
				case OpCodeOperandKind::zmm_or_mem:
					WriteRegMem("zmm", GetVecIndex(i));
					break;
				case OpCodeOperandKind::tmm_reg:
				case OpCodeOperandKind::tmm_rm:
				case OpCodeOperandKind::tmm_vvvv:
					WriteRegOp("tmm", GetTmmIndex());
					break;
				case OpCodeOperandKind::bnd_or_mem_mpx:
					WriteRegOp("bnd", GetBndIndex());
					sb->append('/');
					WriteMemory();
					break;
				case OpCodeOperandKind::k_or_mem:
					WriteRegMem("k", GetKIndex());
					break;
				case OpCodeOperandKind::r8_reg:
				case OpCodeOperandKind::r8_opcode:
					WriteRegOp("r8");
					break;
				case OpCodeOperandKind::r16_reg:
				case OpCodeOperandKind::r16_reg_mem:
				case OpCodeOperandKind::r16_rm:
				case OpCodeOperandKind::r16_opcode:
					WriteRegOp("r16");
					break;
				case OpCodeOperandKind::r32_reg:
				case OpCodeOperandKind::r32_reg_mem:
				case OpCodeOperandKind::r32_rm:
				case OpCodeOperandKind::r32_opcode:
				case OpCodeOperandKind::r32_vvvv:
					WriteRegOp("r32");
					AppendGprSuffix(r32_count, r32_index);
					break;
				case OpCodeOperandKind::r64_reg:
				case OpCodeOperandKind::r64_reg_mem:
				case OpCodeOperandKind::r64_rm:
				case OpCodeOperandKind::r64_opcode:
				case OpCodeOperandKind::r64_vvvv:
					WriteRegOp("r64");
					AppendGprSuffix(r64_count, r64_index);
					break;
				case OpCodeOperandKind::seg_reg:
					sb->append("Sreg");
					break;
				case OpCodeOperandKind::k_reg:
				case OpCodeOperandKind::k_rm:
				case OpCodeOperandKind::k_vvvv:
					WriteRegOp("k", GetKIndex());
					break;
				case OpCodeOperandKind::kp1_reg:
					WriteRegOp("k", GetKIndex());
					sb->append("+1");
					break;
				case OpCodeOperandKind::mm_reg:
				case OpCodeOperandKind::mm_rm:
					WriteRegOp("mm", GetVecIndex(i));
					break;
				case OpCodeOperandKind::xmm_reg:
				case OpCodeOperandKind::xmm_rm:
				case OpCodeOperandKind::xmm_vvvv:
				case OpCodeOperandKind::xmm_is4:
				case OpCodeOperandKind::xmm_is5:
					WriteRegOp("xmm", GetVecIndex(i));
					break;
				case OpCodeOperandKind::xmmp3_vvvv:
					WriteRegOp("xmm", GetVecIndex(i));
					sb->append("+3");
					break;
				case OpCodeOperandKind::ymm_reg:
				case OpCodeOperandKind::ymm_rm:
				case OpCodeOperandKind::ymm_vvvv:
				case OpCodeOperandKind::ymm_is4:
				case OpCodeOperandKind::ymm_is5:
					WriteRegOp("ymm", GetVecIndex(i));
					break;
				case OpCodeOperandKind::zmm_reg:
				case OpCodeOperandKind::zmm_rm:
				case OpCodeOperandKind::zmm_vvvv:
					WriteRegOp("zmm", GetVecIndex(i));
					break;
				case OpCodeOperandKind::zmmp3_vvvv:
					WriteRegOp("zmm", GetVecIndex(i));
					sb->append("+3");
					break;
				case OpCodeOperandKind::bnd_reg:
					WriteRegOp("bnd", GetBndIndex());
					break;
				case OpCodeOperandKind::cr_reg:
					WriteRegOp("cr");
					break;
				case OpCodeOperandKind::dr_reg:
					WriteRegOp("dr");
					break;
				case OpCodeOperandKind::tr_reg:
					WriteRegOp("tr");
					break;
				case OpCodeOperandKind::es:
					WriteRegister("es");
					break;
				case OpCodeOperandKind::cs:
					WriteRegister("cs");
					break;
				case OpCodeOperandKind::ss:
					WriteRegister("ss");
					break;
				case OpCodeOperandKind::ds:
					WriteRegister("ds");
					break;
				case OpCodeOperandKind::fs:
					WriteRegister("fs");
					break;
				case OpCodeOperandKind::gs:
					WriteRegister("gs");
					break;
				case OpCodeOperandKind::al:
					WriteRegister("al");
					break;
				case OpCodeOperandKind::cl:
					WriteRegister("cl");
					break;
				case OpCodeOperandKind::ax:
					WriteRegister("ax");
					break;
				case OpCodeOperandKind::dx:
					WriteRegister("dx");
					break;
				case OpCodeOperandKind::eax:
					WriteRegister("eax");
					break;
				case OpCodeOperandKind::rax:
					WriteRegister("rax");
					break;
				case OpCodeOperandKind::st0:
				case OpCodeOperandKind::sti_opcode:
					WriteRegister("ST");
					if (opKind == OpCodeOperandKind::st0)
					{
						switch (opCode->GetCode())
						{
						case Code::Fcomi_st0_sti:
						case Code::Fcomip_st0_sti:
						case Code::Fucomi_st0_sti:
						case Code::Fucomip_st0_sti:
							break;
						default:
							sb->append("(0)");
							break;
						}
					}
					else
					{
						assert(opKind == OpCodeOperandKind::sti_opcode);
						sb->append("(i)");
					}
					break;
				case OpCodeOperandKind::imm4_m2z:
					sb->append("imm4");
					break;
				case OpCodeOperandKind::imm8:
				case OpCodeOperandKind::imm8sex16:
				case OpCodeOperandKind::imm8sex32:
				case OpCodeOperandKind::imm8sex64:
					sb->append("imm8");
					break;
				case OpCodeOperandKind::imm8_const_1:
					sb->append('1');
					break;
				case OpCodeOperandKind::imm16:
					sb->append("imm16");
					break;
				case OpCodeOperandKind::imm32:
				case OpCodeOperandKind::imm32sex64:
					sb->append("imm32");
					break;
				case OpCodeOperandKind::imm64:
					sb->append("imm64");
					break;
				case OpCodeOperandKind::seg_rSI:
				case OpCodeOperandKind::es_rDI:
				case OpCodeOperandKind::seg_rDI:
				case OpCodeOperandKind::seg_rBX_al:
					addComma = false;
					break;
				case OpCodeOperandKind::br16_1:
				case OpCodeOperandKind::br32_1:
				case OpCodeOperandKind::br64_1:
					sb->append("rel8");
					break;
				case OpCodeOperandKind::br16_2:
				case OpCodeOperandKind::xbegin_2:
					sb->append("rel16");
					break;
				case OpCodeOperandKind::br32_4:
				case OpCodeOperandKind::br64_4:
				case OpCodeOperandKind::xbegin_4:
					sb->append("rel32");
					break;
				case OpCodeOperandKind::brdisp_2:
					sb->append("disp16");
					break;
				case OpCodeOperandKind::brdisp_4:
					sb->append("disp32");
					break;
				case OpCodeOperandKind::None:
				default:
					throw InvalidOperationException();
				}
				if (i == saeErIndex && opCode->GetEncoding() == EncodingKind::MVEX)
				{
					auto mvexInfo = MvexInfo(opCode->GetCode());
					if (mvexInfo.GetConvFn() != MvexConvFn::None)
					{
						sb->append(')');
					}
				}
				if (i == 0)
				{
					if (opCode->GetCanUseOpMaskRegister())
					{
						sb->append(' ');
						WriteRegDecorator("k", GetKIndex());
						if (opCode->GetCanUseZeroingMasking())
						{
							WriteDecorator("z");
						}
					}
				}
				if (i == saeErIndex && opCode->GetEncoding() != EncodingKind::MVEX)
				{
					if (opCode->GetCanSuppressAllExceptions())
					{
						WriteDecorator("sae");
					}
					if (opCode->GetCanUseRoundingControl())
					{
						WriteDecorator("er");
					}
				}
			}
		}
		switch (opCode->GetCode())
		{
			// GENERATOR-BEGIN: PrintImpliedOps
			// ⚠️This was generated by GENERATOR!🦹‍♂️
		case Code::Tpause_r32:
		case Code::Tpause_r64:
		case Code::Umwait_r32:
		case Code::Umwait_r64:
			WriteOpSeparator();
			Write("<EDX>", false);
			WriteOpSeparator();
			Write("<EAX>", false);
			break;
		case Code::Pblendvb_xmm_xmmm128:
		case Code::Blendvps_xmm_xmmm128:
		case Code::Blendvpd_xmm_xmmm128:
		case Code::Sha256rnds2_xmm_xmmm128:
			WriteOpSeparator();
			Write("<XMM0>", true);
			break;
		case Code::Aesencwide128kl_m384:
		case Code::Aesdecwide128kl_m384:
		case Code::Aesencwide256kl_m512:
		case Code::Aesdecwide256kl_m512:
			WriteOpSeparator();
			Write("<XMM0-7>", true);
			break;
		case Code::Loadiwkey_xmm_xmm:
			WriteOpSeparator();
			Write("<EAX>", true);
			WriteOpSeparator();
			Write("<XMM0>", true);
			break;
		case Code::Encodekey128_r32_r32:
			WriteOpSeparator();
			Write("<XMM0-2>", true);
			WriteOpSeparator();
			Write("<XMM4-6>", true);
			break;
		case Code::Encodekey256_r32_r32:
			WriteOpSeparator();
			Write("<XMM0-6>", true);
			break;
		case Code::Hreset_imm8:
			WriteOpSeparator();
			Write("<EAX>", true);
			break;
			// GENERATOR-END: PrintImpliedOps
		default:
			break;
		}
		return sb->toString();
	}

	void InstructionFormatter::WriteMemorySize(MemorySize memorySize)
	{
		switch (opCode->GetCode())
		{
		case Code::Fldcw_m2byte:
		case Code::Fnstcw_m2byte:
		case Code::Fstcw_m2byte:
		case Code::Fnstsw_m2byte:
		case Code::Fstsw_m2byte:
			sb->append("2byte");
			return;
		}
		switch (memorySize)
		{
		case MemorySize::Bound16_WordWord:
			sb->append("16&16");
			break;
		case MemorySize::Bound32_DwordDword:
			sb->append("32&32");
			break;
		case MemorySize::FpuEnv14:
			sb->append("14byte");
			break;
		case MemorySize::FpuEnv28:
			sb->append("28byte");
			break;
		case MemorySize::FpuState94:
			sb->append("94byte");
			break;
		case MemorySize::FpuState108:
			sb->append("108byte");
			break;
		case MemorySize::Fxsave_512Byte:
		case MemorySize::Fxsave64_512Byte:
			sb->append("512byte");
			break;
		case MemorySize::Xsave:
		case MemorySize::Xsave64:
			// 'm' has already been appended
			sb->append("em");
			break;
		case MemorySize::SegPtr16:
			sb->append("16:16");
			break;
		case MemorySize::SegPtr32:
			sb->append("16:32");
			break;
		case MemorySize::SegPtr64:
			sb->append("16:64");
			break;
		case MemorySize::Fword6:
			if (!IsSgdtOrSidt())
			{
				sb->append("16&32");
			}
			break;
		case MemorySize::Fword10:
			if (!IsSgdtOrSidt())
			{
				sb->append("16&64");
			}
			break;
		default:
			std::int32_t memSize = Iced::Intel::MemorySizeExtensions::GetSize(memorySize);
			if (memSize != 0)
			{
				sb->append(memSize * 8);
			}
			break;
		}
		if (IsFpuInstruction(opCode->GetCode()))
		{
			switch (memorySize)
			{
			case MemorySize::Int16:
			case MemorySize::Int32:
			case MemorySize::Int64:
				sb->append("int");
				break;
			case MemorySize::Float32:
			case MemorySize::Float64:
			case MemorySize::Float80:
				sb->append("fp");
				break;
			case MemorySize::Bcd:
				sb->append("bcd");
				break;
			}
		}
	}

	bool InstructionFormatter::IsSgdtOrSidt()
	{
		auto switchTempVar_1 = opCode->GetCode();

		return (switchTempVar_1 == Code::Sgdt_m1632_16 || switchTempVar_1 == Code::Sgdt_m1632 || switchTempVar_1 == Code::Sgdt_m1664 || switchTempVar_1 == Code::Sidt_m1632_16 || switchTempVar_1 == Code::Sidt_m1632 || switchTempVar_1 == Code::Sidt_m1664) ? true : false;
	}

	void InstructionFormatter::WriteRegister(const std::string& register_)
	{
		Write(register_, true);
	}

	void InstructionFormatter::WriteRegOp(const std::string& register_)
	{
		Write(register_, false);
	}

	void InstructionFormatter::WriteRegOp(const std::string& register_, std::int32_t index)
	{
		WriteRegOp(register_);
		if (index > 0)
		{
			sb->append(index);
		}
	}

	void InstructionFormatter::WriteDecorator(const std::string& decorator)
	{
		sb->append('{');
		Write(decorator, false);
		sb->append('}');
	}

	void InstructionFormatter::WriteRegDecorator(const std::string& register_, std::int32_t index)
	{
		sb->append('{');
		Write(register_, false);
		sb->append(index);
		sb->append('}');
	}

	void InstructionFormatter::AppendGprSuffix(std::int32_t count, std::int32_t& index)
	{
		if (count <= 1 || noGprSuffix)
		{
			return;
		}
		sb->append(static_cast<char>('a' + index));
		index++;
	}

	void InstructionFormatter::WriteOpSeparator()
	{
		sb->append(", ");
	}

	void InstructionFormatter::Write(const std::string& s, bool upper)
	{
		for (std::int32_t i = 0; i < s.length(); i++)
		{
			auto c = s[i];
			c = upper ? toupper(c) : tolower(c);
			sb->append(c);
		}
	}

	void InstructionFormatter::WriteGprMem(std::int32_t regSize)
	{
		assert(!opCode->GetCanBroadcast());
		sb->append('r');
		std::int32_t memSize = Iced::Intel::MemorySizeExtensions::GetSize(GetMemorySize(false)) * 8;
		if (memSize != regSize)
		{
			sb->append(regSize);
		}
		sb->append('/');
		WriteMemory();
	}

	void InstructionFormatter::WriteRegMem(const std::string& register_, std::int32_t index)
	{
		WriteRegOp(register_, index);
		sb->append('/');
		WriteMemory();
	}

	void InstructionFormatter::WriteMemory()
	{
		WriteMemory(false);
		if (opCode->GetCanBroadcast())
		{
			sb->append('/');
			WriteMemory(true);
		}
	}

	void InstructionFormatter::WriteMemory(bool isBroadcast)
	{
		auto memorySize = GetMemorySize(isBroadcast);
		sb->append('m');
		if (opCode->GetEncoding() == EncodingKind::MVEX)
		{
			auto mvexInfo = MvexInfo(opCode->GetCode());
			if (mvexInfo.GetEHBit() == MvexEHBit::None && !mvexInfo.GetIgnoresEvictionHint())
			{
				sb->append('t');
			}
		}
		WriteMemorySize(memorySize);
		if (isBroadcast)
		{
			sb->append("bcst");
		}
	}

	bool InstructionFormatter::IsFpuInstruction(Code code)
	{
		return static_cast<std::uint32_t>(code - Code::Fadd_m32fp) <= static_cast<std::uint32_t>(Code::Fcomip_st0_sti - Code::Fadd_m32fp);
	}
}
