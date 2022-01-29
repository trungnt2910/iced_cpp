// C# helper headers




// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "Instruction.Info.h"

namespace Iced::Intel
{

	FpuStackIncrementInfo::FpuStackIncrementInfo(std::int32_t increment, bool conditional, bool writesTop)
	{
		Increment = increment;
		Conditional = conditional;
		WritesTop = writesTop;
	}
}
