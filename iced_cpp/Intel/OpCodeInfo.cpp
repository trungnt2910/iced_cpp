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

#include "OpCodeInfo.h"
#include "Iced.Intel.IcedConstants.h"
#include "MandatoryPrefixByte.g.h"
#include "InstructionOpCounts.g.h"
#include "CodeSize.g.h"
#include "EncoderInternal/OpCodeFormatter.h"
#include "MvexInfo.h"
#include "EncoderInternal/OpCodeOperandKinds.g.h"
#include "EncoderInternal/InstructionFormatter.h"
#include "MnemonicUtils.h"
#include "InstructionMemorySizes.g.h"

using namespace Iced::Intel::EncoderInternal;

namespace Iced::Intel
{

	OpCodeInfo::OpCodeInfo(Iced::Intel::Code code, EncFlags1 encFlags1, EncFlags2 encFlags2, EncFlags3 encFlags3, OpCodeInfoFlags1 opcFlags1, OpCodeInfoFlags2 opcFlags2, std::string& sb)
		: OpCodeInfo(code, encFlags1, encFlags2, encFlags3, opcFlags1, opcFlags2, false)
	{
		assert(static_cast<std::uint32_t>(code) < static_cast<std::uint32_t>(IcedConstants::CodeEnumCount));
		assert(static_cast<std::uint32_t>(code) <= std::numeric_limits<std::uint16_t>::max());

		std::string toOpCodeStringValue = "";
		std::string toInstructionStringValue = "";

		this->toOpCodeStringValue = (toOpCodeStringValue != "") ? toOpCodeStringValue : (OpCodeFormatter(*this, sb, lkind, (opcFlags1 & OpCodeInfoFlags1::ModRegRmString) != 0)).Format();
		auto fmtOption = static_cast<InstrStrFmtOption>((static_cast<std::uint32_t>(opcFlags2) >> static_cast<std::int32_t>(OpCodeInfoFlags2::InstrStrFmtOptionShift)) & static_cast<std::uint32_t>(OpCodeInfoFlags2::InstrStrFmtOptionMask));
		this->toInstructionStringValue = (toInstructionStringValue != "") ? toInstructionStringValue : (InstructionFormatter(*this, fmtOption, sb)).Format();
	}
}