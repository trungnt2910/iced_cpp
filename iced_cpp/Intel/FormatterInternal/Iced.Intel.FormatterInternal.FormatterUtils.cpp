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

#include "Iced.Intel.FormatterInternal.FormatterUtils.h"
#include "../Static.h"
#include "../CodeExtensions.h"
#include "../FormatterTextKind.g.h"

namespace Iced::Intel::FormatterInternal
{

	bool FormatterUtils::IsNotrackPrefixBranch(Code code)
	{
		Static::Assert(Code::Jmp_rm16 + 1 == Code::Jmp_rm32 ? 0 : -1);
		Static::Assert(Code::Jmp_rm16 + 2 == Code::Jmp_rm64 ? 0 : -1);
		Static::Assert(Code::Call_rm16 + 1 == Code::Call_rm32 ? 0 : -1);
		Static::Assert(Code::Call_rm16 + 2 == Code::Call_rm64 ? 0 : -1);
		return static_cast<std::uint32_t>(code) - static_cast<std::uint32_t>(Code::Jmp_rm16) <= 2 || static_cast<std::uint32_t>(code) - static_cast<std::uint32_t>(Code::Call_rm16) <= 2;
	}

	bool FormatterUtils::IsCode64(CodeSize codeSize)
	{
		return codeSize == CodeSize::Code64 || codeSize == CodeSize::Unknown;
	}

	Iced::Intel::Register FormatterUtils::GetDefaultSegmentRegister(const Instruction& instruction)
	{
		auto baseReg = instruction.GetMemoryBase();
		if (baseReg == Register::BP || baseReg == Register::EBP || baseReg == Register::ESP || baseReg == Register::RBP || baseReg == Register::RSP)
		{
			return Register::SS;
		}
		return Register::DS;
	}

	bool FormatterUtils::ShowSegmentPrefix(Register defaultSegReg, const Instruction& instruction, bool showUselessPrefixes)
	{
		if (Iced::Intel::CodeExtensions::IgnoresSegment(instruction.GetCode()))
		{
			return showUselessPrefixes;
		}
		auto prefixSeg = instruction.GetSegmentPrefix();
		assert(prefixSeg != Register::None);
		if (IsCode64(instruction.GetCodeSize()))
		{
			// ES,CS,SS,DS are ignored
			if (prefixSeg == Register::FS || prefixSeg == Register::GS)
			{
				return true;
			}
			return showUselessPrefixes;
		}
		else
		{
			if (defaultSegReg == Register::None)
			{
				defaultSegReg = GetDefaultSegmentRegister(instruction);
			}
			if (prefixSeg != defaultSegReg)
			{
				return true;
			}
			return showUselessPrefixes;
		}
	}

	bool FormatterUtils::ShowRepOrRepePrefix(Code code, bool showUselessPrefixes)
	{
		if (showUselessPrefixes || IsRepRepeRepneInstruction(code))
		{
			return true;
		}
		switch (code)
		{
			// We allow 'rep ret' too since some old code use it to work around an old AMD bug
		case Code::Retnw:
		case Code::Retnd:
		case Code::Retnq:
			return true;
		default:
			return showUselessPrefixes;
		}
	}

	bool FormatterUtils::ShowRepnePrefix(Code code, bool showUselessPrefixes)
	{
		// If it's a 'rep/repne' instruction, always show the prefix
		if (showUselessPrefixes || IsRepRepeRepneInstruction(code))
		{
			return true;
		}
		return showUselessPrefixes;
	}

	bool FormatterUtils::IsRepeOrRepneInstruction(Code code)
	{
		switch (code)
		{
		case Code::Cmpsb_m8_m8:
		case Code::Cmpsw_m16_m16:
		case Code::Cmpsd_m32_m32:
		case Code::Cmpsq_m64_m64:
		case Code::Scasb_AL_m8:
		case Code::Scasw_AX_m16:
		case Code::Scasd_EAX_m32:
		case Code::Scasq_RAX_m64:
			return true;
		default:
			return false;
		}
	}

	bool FormatterUtils::IsRepRepeRepneInstruction(Code code)
	{
		switch (code)
		{
		case Code::Insb_m8_DX:
		case Code::Insw_m16_DX:
		case Code::Insd_m32_DX:
		case Code::Outsb_DX_m8:
		case Code::Outsw_DX_m16:
		case Code::Outsd_DX_m32:
		case Code::Movsb_m8_m8:
		case Code::Movsw_m16_m16:
		case Code::Movsd_m32_m32:
		case Code::Movsq_m64_m64:
		case Code::Cmpsb_m8_m8:
		case Code::Cmpsw_m16_m16:
		case Code::Cmpsd_m32_m32:
		case Code::Cmpsq_m64_m64:
		case Code::Stosb_m8_AL:
		case Code::Stosw_m16_AX:
		case Code::Stosd_m32_EAX:
		case Code::Stosq_m64_RAX:
		case Code::Lodsb_AL_m8:
		case Code::Lodsw_AX_m16:
		case Code::Lodsd_EAX_m32:
		case Code::Lodsq_RAX_m64:
		case Code::Scasb_AL_m8:
		case Code::Scasw_AX_m16:
		case Code::Scasd_EAX_m32:
		case Code::Scasq_RAX_m64:
		case Code::Montmul_16:
		case Code::Montmul_32:
		case Code::Montmul_64:
		case Code::Xsha1_16:
		case Code::Xsha1_32:
		case Code::Xsha1_64:
		case Code::Xsha256_16:
		case Code::Xsha256_32:
		case Code::Xsha256_64:
		case Code::Xstore_16:
		case Code::Xstore_32:
		case Code::Xstore_64:
		case Code::Xcryptecb_16:
		case Code::Xcryptecb_32:
		case Code::Xcryptecb_64:
		case Code::Xcryptcbc_16:
		case Code::Xcryptcbc_32:
		case Code::Xcryptcbc_64:
		case Code::Xcryptctr_16:
		case Code::Xcryptctr_32:
		case Code::Xcryptctr_64:
		case Code::Xcryptcfb_16:
		case Code::Xcryptcfb_32:
		case Code::Xcryptcfb_64:
		case Code::Xcryptofb_16:
		case Code::Xcryptofb_32:
		case Code::Xcryptofb_64:
		case Code::Ccs_hash_16:
		case Code::Ccs_hash_32:
		case Code::Ccs_hash_64:
		case Code::Ccs_encrypt_16:
		case Code::Ccs_encrypt_32:
		case Code::Ccs_encrypt_64:
			return true;
		default:
			return false;
		}
	}

	std::vector<std::string> FormatterUtils::spaceStrings = CreateStrings(' ', 20);
	std::vector<std::string> FormatterUtils::tabStrings = CreateStrings('\t', 6);

	std::vector<std::string> FormatterUtils::CreateStrings(char c, std::int32_t max)
	{
		auto strings = std::vector<std::string>(max);
		for (std::int32_t i = 0; i < strings.size(); i++)
		{
			strings[i] = std::string(i + 1, c);
		}
		return strings;
	}

	void FormatterUtils::AddTabs(FormatterOutput& output, std::int32_t column, std::int32_t firstOperandCharIndex, std::int32_t tabSize)
	{
		constexpr std::int32_t max_firstOperandCharIndex = 256;
		if (firstOperandCharIndex < 0)
		{
			firstOperandCharIndex = 0;
		}
		else if (firstOperandCharIndex > max_firstOperandCharIndex)
		{
			firstOperandCharIndex = max_firstOperandCharIndex;
		}
		if (tabSize <= 0)
		{
			std::int32_t charsLeft = firstOperandCharIndex - column;
			if (charsLeft <= 0)
			{
				charsLeft = 1;
			}
			AddStrings(output, spaceStrings, charsLeft);
		}
		else
		{
			std::int32_t endCol = firstOperandCharIndex;
			if (endCol <= column)
			{
				endCol = column + 1;
			}
			std::int32_t endColRoundedDown = endCol / tabSize * tabSize;
			bool addedTabs = endColRoundedDown > column;
			if (addedTabs)
			{
				std::int32_t tabs = (endColRoundedDown - (column / tabSize * tabSize)) / tabSize;
				AddStrings(output, tabStrings, tabs);
				column = endColRoundedDown;
			}
			std::int32_t spaces = firstOperandCharIndex - column;
			if (spaces > 0)
			{
				AddStrings(output, spaceStrings, spaces);
			}
			else if (!addedTabs)
			{
				AddStrings(output, spaceStrings, 1);
			}
		}
	}

	void FormatterUtils::AddStrings(FormatterOutput& output, std::vector<std::string>& strings, std::int32_t count)
	{
		while (count > 0)
		{
			std::int32_t n = count;
			if (n >= strings.size())
			{
				n = (std::int32_t)strings.size();
			}
			output.Write(strings[n - 1], FormatterTextKind::Text);
			count -= n;
		}
	}

	bool FormatterUtils::IsCall(FormatterFlowControl kind)
	{
		return kind == FormatterFlowControl::NearCall || kind == FormatterFlowControl::FarCall;
	}

	FormatterFlowControl FormatterUtils::GetFlowControl(const Instruction& instruction)
	{
		switch (instruction.GetCode())
		{
			// GENERATOR-BEGIN: FormatterFlowControlSwitch
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
		case Code::Jmp_rel8_16:
		case Code::Jmp_rel8_32:
		case Code::Jmp_rel8_64:
		case Code::VEX_KNC_Jkzd_kr_rel8_64:
		case Code::VEX_KNC_Jknzd_kr_rel8_64:
			return FormatterFlowControl::ShortBranch;
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
			return FormatterFlowControl::AlwaysShortBranch;
		case Code::Call_rel16:
		case Code::Call_rel32_32:
		case Code::Call_rel32_64:
			return FormatterFlowControl::NearCall;
		case Code::Jmp_rel16:
		case Code::Jmp_rel32_32:
		case Code::Jmp_rel32_64:
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
		case Code::Jmpe_disp16:
		case Code::Jmpe_disp32:
		case Code::VEX_KNC_Jkzd_kr_rel32_64:
		case Code::VEX_KNC_Jknzd_kr_rel32_64:
			return FormatterFlowControl::NearBranch;
		case Code::Call_ptr1616:
		case Code::Call_ptr1632:
			return FormatterFlowControl::FarCall;
		case Code::Jmp_ptr1616:
		case Code::Jmp_ptr1632:
			return FormatterFlowControl::FarBranch;
		case Code::Xbegin_rel16:
		case Code::Xbegin_rel32:
			return FormatterFlowControl::Xbegin;
			// GENERATOR-END: FormatterFlowControlSwitch
		default:
			throw InvalidOperationException();
		}
	}

	bool FormatterUtils::ShowRepOrRepePrefix(Code code, const FormatterOptions& options)
	{
		return ShowRepOrRepePrefix(code, options.GetShowUselessPrefixes());
	}

	bool FormatterUtils::ShowRepnePrefix(Code code, const FormatterOptions& options)
	{
		return ShowRepnePrefix(code, options.GetShowUselessPrefixes());
	}

	Iced::Intel::PrefixKind FormatterUtils::GetSegmentRegisterPrefixKind(Register register_)
	{
		assert(register_ == Register::ES || register_ == Register::CS || register_ == Register::SS || register_ == Register::DS || register_ == Register::FS || register_ == Register::GS);
		Static::Assert(PrefixKind::ES + 1 == PrefixKind::CS ? 0 : -1);
		Static::Assert(PrefixKind::ES + 2 == PrefixKind::SS ? 0 : -1);
		Static::Assert(PrefixKind::ES + 3 == PrefixKind::DS ? 0 : -1);
		Static::Assert(PrefixKind::ES + 4 == PrefixKind::FS ? 0 : -1);
		Static::Assert(PrefixKind::ES + 5 == PrefixKind::GS ? 0 : -1);
		return (PrefixKind)((register_ - Register::ES) + PrefixKind::ES);
	}

	bool FormatterUtils::ShowIndexScale(const Instruction& instruction, const FormatterOptions& options)
	{
		return options.GetShowUselessPrefixes() || !Iced::Intel::CodeExtensions::IgnoresIndex(instruction.GetCode());
	}

	bool FormatterUtils::ShowSegmentPrefix(Register defaultSegReg, const Instruction& instruction, const FormatterOptions& options)
	{
		return ShowSegmentPrefix(defaultSegReg, instruction, options.GetShowUselessPrefixes());
	}

	bool FormatterUtils::CanShowRoundingControl(const Instruction& instruction, const FormatterOptions& options)
	{
		switch (instruction.GetCode())
		{
		case Code::EVEX_Vcvtsi2sd_xmm_xmm_rm32_er:
		case Code::EVEX_Vcvtusi2sd_xmm_xmm_rm32_er:
		case Code::EVEX_Vcvtdq2pd_zmm_k1z_ymmm256b32_er:
		case Code::EVEX_Vcvtudq2pd_zmm_k1z_ymmm256b32_er:
			return options.GetShowUselessPrefixes();
		default:
			return true;
		}
	}
}
