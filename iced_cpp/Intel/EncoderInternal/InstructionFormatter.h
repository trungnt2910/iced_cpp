#pragma once

#include "InstructionFormatter.defs.h"
#include "../EncodingKind.g.h"
#include "../OpCodeOperandKind.g.h"
#include "../InstructionMemorySizes.g.h"
#include "../MvexInfo.h"
#include "../MvexConvFn.g.h"
#include "../MemorySizeExtensions.h"
#include "../MvexEHBit.g.h"
#include "../OpCodeInfo.h"
#include "../Internal/StringHelpers.h"

namespace Iced::Intel::EncoderInternal
{
	constexpr std::int32_t InstructionFormatter::GetKIndex()
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

	constexpr std::int32_t InstructionFormatter::GetBndIndex()
	{
		if (bnd_count <= 1)
		{
			return 0;
		}
		bnd_index++;
		return bnd_index;
	}

	constexpr std::int32_t InstructionFormatter::GetVecIndex(std::int32_t opIndex)
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

	constexpr std::int32_t InstructionFormatter::GetTmmIndex()
	{
		tmm_index++;
		return tmm_index;
	}

	inline InstructionFormatter::InstructionFormatter(const OpCodeInfo& opCode, InstrStrFmtOption fmtOption, std::string& sb) : InstructionFormatter(opCode, fmtOption, false)
	{
		this->sb = &sb;
	}

	constexpr InstructionFormatter::InstructionFormatter(const OpCodeInfo& opCode, InstrStrFmtOption fmtOption) : InstructionFormatter(opCode, fmtOption, true)
	{
	}

	constexpr InstructionFormatter::InstructionFormatter(const OpCodeInfo& opCode, InstrStrFmtOption fmtOption, bool constructString) : isConstexprEval(std::is_constant_evaluated())
	{
		if (isConstexprEval)
		{
			this->opCode = new OpCodeInfo(opCode);
			this->sb = new std::string();
		}
		else
		{
			this->opCode = &opCode;
			if (constructString)
			{
				this->sb = new std::string();
				ownsSb = true;
			}
		}

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
		opCount = opCode.GetOpCount();
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
			throw std::runtime_error("invalid operation");
		}
		if ((opCode.GetOp0Kind() == OpCodeOperandKind::k_reg || opCode.GetOp0Kind() == OpCodeOperandKind::kp1_reg) && opCode.GetOpCount() > 2 && opCode.GetEncoding() != EncodingKind::MVEX)
		{
			vecIndexSameAsOpIndex = true;
		}
		for (std::int32_t i = 0; i < opCode.GetOpCount(); i++)
		{
			switch (opCode.GetOpKind(i))
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
				throw std::runtime_error("invalid operation");
			}
		}
	}

	constexpr InstructionFormatter::~InstructionFormatter()
	{
		if (isConstexprEval)
		{
			delete sb;
			delete opCode;
		}
		else if (ownsSb)
		{
			delete sb;
		}
	}

	constexpr ::Iced::Intel::MemorySize InstructionFormatter::GetMemorySize(bool isBroadcast)
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

	constexpr std::string InstructionFormatter::Format()
	{
		if (!opCode->IsInstruction())
		{
			auto switchTempVar_0 = opCode->GetCode();
			// GENERATOR-BEGIN: InstrFmtNotInstructionString
			// ⚠️This was generated by GENERATOR!🦹‍♂️
			// GENERATOR-END: InstrFmtNotInstructionString

			return (switchTempVar_0 == Code::INVALID) ? "<invalid>" : (switchTempVar_0 == Code::DeclareByte) ? "<db>" : (switchTempVar_0 == Code::DeclareWord) ? "<dw>" : (switchTempVar_0 == Code::DeclareDword) ? "<dd>" : (switchTempVar_0 == Code::DeclareQword) ? "<dq>" : throw std::runtime_error("invalid operation");
		}
		sb->clear();
		//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
		Write(ToString(opCode->GetMnemonic()), true);
		if (startOpIndex < opCount)
		{
			sb->push_back(' ');
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
						sb->push_back('(');
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
					sb->push_back('/');
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
					sb->push_back('1');
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
					throw std::runtime_error("invalid operation");
				}
				if (i == saeErIndex && opCode->GetEncoding() == EncodingKind::MVEX)
				{
					auto mvexInfo = MvexInfo(opCode->GetCode());
					if (mvexInfo.GetConvFn() != MvexConvFn::None)
					{
						sb->push_back(')');
					}
				}
				if (i == 0)
				{
					if (opCode->GetCanUseOpMaskRegister())
					{
						sb->push_back(' ');
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
		return *sb;
	}

	constexpr void InstructionFormatter::WriteMemorySize(MemorySize memorySize)
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
			std::int32_t memSize = ::Iced::Intel::MemorySizeExtensions::GetSize(memorySize);
			if (memSize != 0)
			{
				sb->append(Internal::StringHelpers::ToDec((std::uint32_t)(memSize * 8)));
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

	constexpr bool InstructionFormatter::IsSgdtOrSidt()
	{
		auto switchTempVar_1 = opCode->GetCode();

		return (switchTempVar_1 == Code::Sgdt_m1632_16 || switchTempVar_1 == Code::Sgdt_m1632 || switchTempVar_1 == Code::Sgdt_m1664 || switchTempVar_1 == Code::Sidt_m1632_16 || switchTempVar_1 == Code::Sidt_m1632 || switchTempVar_1 == Code::Sidt_m1664) ? true : false;
	}

	constexpr void InstructionFormatter::WriteRegister(const std::string& register_)
	{
		Write(register_, true);
	}

	constexpr void InstructionFormatter::WriteRegOp(const std::string& register_)
	{
		Write(register_, false);
	}

	constexpr void InstructionFormatter::WriteRegOp(const std::string& register_, std::int32_t index)
	{
		WriteRegOp(register_);
		if (index > 0)
		{
			sb->append(Internal::StringHelpers::ToDec((std::uint32_t)index));
		}
	}

	constexpr void InstructionFormatter::WriteDecorator(const std::string& decorator)
	{
		sb->push_back('{');
		Write(decorator, false);
		sb->push_back('}');
	}

	constexpr void InstructionFormatter::WriteRegDecorator(const std::string& register_, std::int32_t index)
	{
		sb->push_back('{');
		Write(register_, false);
		sb->append(Internal::StringHelpers::ToDec((std::uint32_t)index));
		sb->push_back('}');
	}

	constexpr void InstructionFormatter::AppendGprSuffix(std::int32_t count, std::int32_t& index)
	{
		if (count <= 1 || noGprSuffix)
		{
			return;
		}
		sb->push_back(static_cast<char>('a' + index));
		index++;
	}

	constexpr void InstructionFormatter::WriteOpSeparator()
	{
		sb->append(", ");
	}

	constexpr void InstructionFormatter::Write(const std::string& s, bool upper)
	{
		for (std::int32_t i = 0; i < s.length(); i++)
		{
			auto c = s[i];
			c = upper ? Internal::StringHelpers::ToUpper(c) : Internal::StringHelpers::ToLower(c);
			sb->push_back(c);
		}
	}

	constexpr void InstructionFormatter::WriteGprMem(std::int32_t regSize)
	{
		assert(!opCode->GetCanBroadcast());
		sb->push_back('r');
		std::int32_t memSize = ::Iced::Intel::MemorySizeExtensions::GetSize(GetMemorySize(false)) * 8;
		if (memSize != regSize)
		{
			sb->append(Internal::StringHelpers::ToDec((std::uint32_t)regSize));
		}
		sb->push_back('/');
		WriteMemory();
	}

	constexpr void InstructionFormatter::WriteRegMem(const std::string& register_, std::int32_t index)
	{
		WriteRegOp(register_, index);
		sb->push_back('/');
		WriteMemory();
	}

	constexpr void InstructionFormatter::WriteMemory()
	{
		WriteMemory(false);
		if (opCode->GetCanBroadcast())
		{
			sb->push_back('/');
			WriteMemory(true);
		}
	}

	constexpr void InstructionFormatter::WriteMemory(bool isBroadcast)
	{
		auto memorySize = GetMemorySize(isBroadcast);
		sb->push_back('m');
		if (opCode->GetEncoding() == EncodingKind::MVEX)
		{
			auto mvexInfo = MvexInfo(opCode->GetCode());
			if (mvexInfo.GetEHBit() == MvexEHBit::None && !mvexInfo.GetIgnoresEvictionHint())
			{
				sb->push_back('t');
			}
		}
		WriteMemorySize(memorySize);
		if (isBroadcast)
		{
			sb->append("bcst");
		}
	}

	constexpr bool InstructionFormatter::IsFpuInstruction(Code code)
	{
		return static_cast<std::uint32_t>(code - Code::Fadd_m32fp) <= static_cast<std::uint32_t>(Code::Fcomip_st0_sti - Code::Fadd_m32fp);
	}
}
