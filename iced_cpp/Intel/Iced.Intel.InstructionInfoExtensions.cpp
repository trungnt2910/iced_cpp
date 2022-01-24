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

#include "Iced.Intel.InstructionInfoExtensions.h"
#include "InstructionInfoInternal/InstrInfoTable.g.h"
#include "ThrowHelper.h"
#include "InstructionInfoInternal/InfoHandlerFlags.h"
#include "InstructionInfoInternal/CpuidFeatureInternal.g.h"
#include "InstructionInfoInternal/Iced.Intel.InstructionInfoInternal.CpuidFeatureInternalData.h"
#include "Static.h"

using namespace Iced::Intel::InstructionInfoInternal;

namespace Iced::Intel
{

	EncodingKind InstructionInfoExtensions::Encoding(Code code)
	{
		auto data = InstrInfoTable::Data;
		std::int32_t index = static_cast<std::int32_t>(code) * 2 + 1;
		if (static_cast<std::uint32_t>(index) >= static_cast<std::uint32_t>(data.size()))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_code();
		}
		return static_cast<EncodingKind>((data[index] >> static_cast<std::int32_t>(InfoFlags2::EncodingShift)) & static_cast<std::uint32_t>(InfoFlags2::EncodingMask));
	}

	std::vector<CpuidFeature> InstructionInfoExtensions::CpuidFeatures(Code code)
	{
		auto data = InstrInfoTable::Data;
		std::int32_t index = static_cast<std::int32_t>(code) * 2 + 1;
		if (static_cast<std::uint32_t>(index) >= static_cast<std::uint32_t>(data.size()))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_code();
		}
		auto cpuidFeature = static_cast<CpuidFeatureInternal>((data[index] >> static_cast<std::int32_t>(InfoFlags2::CpuidFeatureInternalShift)) & static_cast<std::uint32_t>(InfoFlags2::CpuidFeatureInternalMask));
		return CpuidFeatureInternalData::ToCpuidFeatures[static_cast<std::int32_t>(cpuidFeature)];
	}

	Iced::Intel::FlowControl InstructionInfoExtensions::FlowControl(Code code)
	{
		auto data = InstrInfoTable::Data;
		std::int32_t index = static_cast<std::int32_t>(code) * 2 + 1;
		if (static_cast<std::uint32_t>(index) >= static_cast<std::uint32_t>(data.size()))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_code();
		}
		return static_cast<Iced::Intel::FlowControl>((data[index] >> static_cast<std::int32_t>(InfoFlags2::FlowControlShift)) & static_cast<std::uint32_t>(InfoFlags2::FlowControlMask));
	}

	bool InstructionInfoExtensions::IsPrivileged(Code code)
	{
		auto data = InstrInfoTable::Data;
		std::int32_t index = static_cast<std::int32_t>(code) * 2 + 1;
		if (static_cast<std::uint32_t>(index) >= static_cast<std::uint32_t>(data.size()))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_code();
		}
		return (data[index] & static_cast<std::uint32_t>(InfoFlags2::Privileged)) != 0;
	}

	bool InstructionInfoExtensions::IsStackInstruction(Code code)
	{
		auto data = InstrInfoTable::Data;
		std::int32_t index = static_cast<std::int32_t>(code) * 2 + 1;
		if (static_cast<std::uint32_t>(index) >= static_cast<std::uint32_t>(data.size()))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_code();
		}
		return (data[index] & static_cast<std::uint32_t>(InfoFlags2::StackInstruction)) != 0;
	}

	bool InstructionInfoExtensions::IsSaveRestoreInstruction(Code code)
	{
		auto data = InstrInfoTable::Data;
		std::int32_t index = static_cast<std::int32_t>(code) * 2 + 1;
		if (static_cast<std::uint32_t>(index) >= static_cast<std::uint32_t>(data.size()))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_code();
		}
		return (data[index] & static_cast<std::uint32_t>(InfoFlags2::SaveRestore)) != 0;
	}

	bool InstructionInfoExtensions::IsJccNear(Code code)
	{
		return static_cast<std::uint32_t>(code - Code::Jo_rel16) <= static_cast<std::uint32_t>(Code::Jg_rel32_64 - Code::Jo_rel16);
	}

	bool InstructionInfoExtensions::IsJccShort(Code code)
	{
		return static_cast<std::uint32_t>(code - Code::Jo_rel8_16) <= static_cast<std::uint32_t>(Code::Jg_rel8_64 - Code::Jo_rel8_16);
	}

	bool InstructionInfoExtensions::IsJmpShort(Code code)
	{
		return static_cast<std::uint32_t>(code - Code::Jmp_rel8_16) <= static_cast<std::uint32_t>(Code::Jmp_rel8_64 - Code::Jmp_rel8_16);
	}

	bool InstructionInfoExtensions::IsJmpNear(Code code)
	{
		return static_cast<std::uint32_t>(code - Code::Jmp_rel16) <= static_cast<std::uint32_t>(Code::Jmp_rel32_64 - Code::Jmp_rel16);
	}

	bool InstructionInfoExtensions::IsJmpShortOrNear(Code code)
	{
		return static_cast<std::uint32_t>(code - Code::Jmp_rel8_16) <= static_cast<std::uint32_t>(Code::Jmp_rel8_64 - Code::Jmp_rel8_16) || static_cast<std::uint32_t>(code - Code::Jmp_rel16) <= static_cast<std::uint32_t>(Code::Jmp_rel32_64 - Code::Jmp_rel16);
	}

	bool InstructionInfoExtensions::IsJmpFar(Code code)
	{
		return static_cast<std::uint32_t>(code - Code::Jmp_ptr1616) <= static_cast<std::uint32_t>(Code::Jmp_ptr1632 - Code::Jmp_ptr1616);
	}

	bool InstructionInfoExtensions::IsCallNear(Code code)
	{
		return static_cast<std::uint32_t>(code - Code::Call_rel16) <= static_cast<std::uint32_t>(Code::Call_rel32_64 - Code::Call_rel16);
	}

	bool InstructionInfoExtensions::IsCallFar(Code code)
	{
		return static_cast<std::uint32_t>(code - Code::Call_ptr1616) <= static_cast<std::uint32_t>(Code::Call_ptr1632 - Code::Call_ptr1616);
	}

	bool InstructionInfoExtensions::IsJmpNearIndirect(Code code)
	{
		return static_cast<std::uint32_t>(code - Code::Jmp_rm16) <= static_cast<std::uint32_t>(Code::Jmp_rm64 - Code::Jmp_rm16);
	}

	bool InstructionInfoExtensions::IsJmpFarIndirect(Code code)
	{
		return static_cast<std::uint32_t>(code - Code::Jmp_m1616) <= static_cast<std::uint32_t>(Code::Jmp_m1664 - Code::Jmp_m1616);
	}

	bool InstructionInfoExtensions::IsCallNearIndirect(Code code)
	{
		return static_cast<std::uint32_t>(code - Code::Call_rm16) <= static_cast<std::uint32_t>(Code::Call_rm64 - Code::Call_rm16);
	}

	bool InstructionInfoExtensions::IsCallFarIndirect(Code code)
	{
		return static_cast<std::uint32_t>(code - Code::Call_m1616) <= static_cast<std::uint32_t>(Code::Call_m1664 - Code::Call_m1616);
	}

	bool InstructionInfoExtensions::IsJkccShortOrNear(Code code)
	{
		return code == Code::VEX_KNC_Jkzd_kr_rel32_64 || code == Code::VEX_KNC_Jknzd_kr_rel32_64 || code == Code::VEX_KNC_Jkzd_kr_rel8_64 || code == Code::VEX_KNC_Jknzd_kr_rel8_64;
	}

	bool InstructionInfoExtensions::IsJkccNear(Code code)
	{
		return code == Code::VEX_KNC_Jkzd_kr_rel32_64 || code == Code::VEX_KNC_Jknzd_kr_rel32_64;
	}

	bool InstructionInfoExtensions::IsJkccShort(Code code)
	{
		return code == Code::VEX_KNC_Jkzd_kr_rel8_64 || code == Code::VEX_KNC_Jknzd_kr_rel8_64;
	}

	Iced::Intel::ConditionCode InstructionInfoExtensions::ConditionCode(Code code)
	{
		std::uint32_t t;
		if ((t = static_cast<std::uint32_t>(code - Code::Jo_rel16)) <= static_cast<std::uint32_t>(Code::Jg_rel32_64 - Code::Jo_rel16) || (t = static_cast<std::uint32_t>(code - Code::Jo_rel8_16)) <= static_cast<std::uint32_t>(Code::Jg_rel8_64 - Code::Jo_rel8_16) || (t = static_cast<std::uint32_t>(code - Code::Cmovo_r16_rm16)) <= static_cast<std::uint32_t>(Code::Cmovg_r64_rm64 - Code::Cmovo_r16_rm16))
		{
			return (Iced::Intel::ConditionCode)(static_cast<std::int32_t>(t / 3) + Intel::ConditionCode::o);
		}
		t = static_cast<std::uint32_t>(code - Code::Seto_rm8);
		if (t <= static_cast<std::uint32_t>(Code::Setg_rm8 - Code::Seto_rm8))
		{
			return (Iced::Intel::ConditionCode)(static_cast<std::int32_t>(t) + Intel::ConditionCode::o);
		}
		t = static_cast<std::uint32_t>(code - Code::Loopne_rel8_16_CX);
		if (t <= static_cast<std::uint32_t>(Code::Loopne_rel8_64_RCX - Code::Loopne_rel8_16_CX))
		{
			return Intel::ConditionCode::ne;
		}
		t = static_cast<std::uint32_t>(code - Code::Loope_rel8_16_CX);
		if (t <= static_cast<std::uint32_t>(Code::Loope_rel8_64_RCX - Code::Loope_rel8_16_CX))
		{
			return Intel::ConditionCode::e;
		}
		switch (code)
		{
		case Code::VEX_KNC_Jkzd_kr_rel8_64:
		case Code::VEX_KNC_Jkzd_kr_rel32_64:
			return Intel::ConditionCode::e;
		case Code::VEX_KNC_Jknzd_kr_rel8_64:
		case Code::VEX_KNC_Jknzd_kr_rel32_64:
			return Intel::ConditionCode::ne;
		default:
			break;
		}
		return Intel::ConditionCode::None;
	}

	bool InstructionInfoExtensions::IsStringInstruction(Code code)
	{
		switch (code)
		{
			// GENERATOR-BEGIN: IsStringOpTable
			// ⚠️This was generated by GENERATOR!🦹‍♂️
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
			return true;
			// GENERATOR-END: IsStringOpTable
		default:
			return false;
		}
	}

	Code InstructionInfoExtensions::NegateConditionCode(Code code)
	{
		std::uint32_t t;
		if ((t = static_cast<std::uint32_t>(code - Code::Jo_rel16)) <= static_cast<std::uint32_t>(Code::Jg_rel32_64 - Code::Jo_rel16) || (t = static_cast<std::uint32_t>(code - Code::Jo_rel8_16)) <= static_cast<std::uint32_t>(Code::Jg_rel8_64 - Code::Jo_rel8_16) || (t = static_cast<std::uint32_t>(code - Code::Cmovo_r16_rm16)) <= static_cast<std::uint32_t>(Code::Cmovg_r64_rm64 - Code::Cmovo_r16_rm16))
		{
			// They're ordered, eg. je_16, je_32, je_64, jne_16, jne_32, jne_64
			// if low 3, add 3, else if high 3, subtract 3.
			//return (((int)((t / 3) << 31) >> 31) | 1) * 3 + code;
			if (((t / 3) & 1) != 0)
			{
				return (Code)(code - 3);
			}
			return (Code)(code + 3);
		}
		t = static_cast<std::uint32_t>(code - Code::Seto_rm8);
		if (t <= static_cast<std::uint32_t>(Code::Setg_rm8 - Code::Seto_rm8))
		{
			return (Code)(static_cast<std::int32_t>(t ^ 1) + Code::Seto_rm8);
		}
		Static::Assert(Code::Loopne_rel8_16_CX + 7 == Code::Loope_rel8_16_CX ? 0 : -1);
		t = static_cast<std::uint32_t>(code - Code::Loopne_rel8_16_CX);
		if (t <= static_cast<std::uint32_t>(Code::Loope_rel8_64_RCX - Code::Loopne_rel8_16_CX))
		{
			return (Code)(Code::Loopne_rel8_16_CX + static_cast<std::int32_t>((t + 7) % 14));
		}
		switch (code)
		{
		case Code::VEX_KNC_Jkzd_kr_rel8_64:
			return Code::VEX_KNC_Jknzd_kr_rel8_64;
		case Code::VEX_KNC_Jknzd_kr_rel8_64:
			return Code::VEX_KNC_Jkzd_kr_rel8_64;
		case Code::VEX_KNC_Jkzd_kr_rel32_64:
			return Code::VEX_KNC_Jknzd_kr_rel32_64;
		case Code::VEX_KNC_Jknzd_kr_rel32_64:
			return Code::VEX_KNC_Jkzd_kr_rel32_64;
		default:
			break;
		}
		return code;
	}

	Code InstructionInfoExtensions::ToShortBranch(Code code)
	{
		std::uint32_t t;
		t = static_cast<std::uint32_t>(code - Code::Jo_rel16);
		if (t <= static_cast<std::uint32_t>(Code::Jg_rel32_64 - Code::Jo_rel16))
		{
			return (Code)(static_cast<std::int32_t>(t) + Code::Jo_rel8_16);
		}
		t = static_cast<std::uint32_t>(code - Code::Jmp_rel16);
		if (t <= static_cast<std::uint32_t>(Code::Jmp_rel32_64 - Code::Jmp_rel16))
		{
			return (Code)(static_cast<std::int32_t>(t) + Code::Jmp_rel8_16);
		}
		switch (code)
		{
		case Code::VEX_KNC_Jkzd_kr_rel32_64:
			return Code::VEX_KNC_Jkzd_kr_rel8_64;
		case Code::VEX_KNC_Jknzd_kr_rel32_64:
			return Code::VEX_KNC_Jknzd_kr_rel8_64;
		default:
			break;
		}
		return code;
	}

	Code InstructionInfoExtensions::ToNearBranch(Code code)
	{
		std::uint32_t t;
		t = static_cast<std::uint32_t>(code - Code::Jo_rel8_16);
		if (t <= static_cast<std::uint32_t>(Code::Jg_rel8_64 - Code::Jo_rel8_16))
		{
			return (Code)(static_cast<std::int32_t>(t) + Code::Jo_rel16);
		}
		t = static_cast<std::uint32_t>(code - Code::Jmp_rel8_16);
		if (t <= static_cast<std::uint32_t>(Code::Jmp_rel8_64 - Code::Jmp_rel8_16))
		{
			return (Code)(static_cast<std::int32_t>(t) + Code::Jmp_rel16);
		}
		switch (code)
		{
		case Code::VEX_KNC_Jkzd_kr_rel8_64:
			return Code::VEX_KNC_Jkzd_kr_rel32_64;
		case Code::VEX_KNC_Jknzd_kr_rel8_64:
			return Code::VEX_KNC_Jknzd_kr_rel32_64;
		default:
			break;
		}
		return code;
	}

	bool InstructionInfoExtensions::IsJccShortOrNear(Code code)
	{
		return static_cast<std::uint32_t>(code - Code::Jo_rel8_16) <= static_cast<std::uint32_t>(Code::Jg_rel8_64 - Code::Jo_rel8_16) || static_cast<std::uint32_t>(code - Code::Jo_rel16) <= static_cast<std::uint32_t>(Code::Jg_rel32_64 - Code::Jo_rel16);
	}

	bool InstructionInfoExtensions::IsJcxShort(Code code)
	{
		return static_cast<std::uint32_t>(code - Code::Jcxz_rel8_16) <= static_cast<std::uint32_t>(Code::Jrcxz_rel8_64 - Code::Jcxz_rel8_16);
	}

	bool InstructionInfoExtensions::IsLoopcc(Code code)
	{
		return static_cast<std::uint32_t>(code - Code::Loopne_rel8_16_CX) <= static_cast<std::uint32_t>(Code::Loope_rel8_64_RCX - Code::Loopne_rel8_16_CX);
	}

	bool InstructionInfoExtensions::IsLoop(Code code)
	{
		return static_cast<std::uint32_t>(code - Code::Loop_rel8_16_CX) <= static_cast<std::uint32_t>(Code::Loop_rel8_64_RCX - Code::Loop_rel8_16_CX);
	}
}
