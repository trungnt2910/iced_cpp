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

#include "InstructionUtils.h"

namespace Iced::Intel
{

	std::int32_t InstructionUtils::GetAddressSizeInBytes(Register baseReg, Register indexReg, std::int32_t displSize, CodeSize codeSize)
	{
		if ((Register::RAX <= baseReg && baseReg <= Register::R15) || (Register::RAX <= indexReg && indexReg <= Register::R15) || baseReg == Register::RIP)
		{
			return 8;
		}
		if ((Register::EAX <= baseReg && baseReg <= Register::R15D) || (Register::EAX <= indexReg && indexReg <= Register::R15D) || baseReg == Register::EIP)
		{
			return 4;
		}
		if ((Register::AX <= baseReg && baseReg <= Register::DI) || (Register::AX <= indexReg && indexReg <= Register::DI))
		{
			return 2;
		}
		if (displSize == 2 || displSize == 4 || displSize == 8)
		{
			return displSize;
		}
		auto switchTempVar_0 = codeSize;


		return (switchTempVar_0 == CodeSize::Code64) ? static_cast<std::uint8_t>(8) : (switchTempVar_0 == CodeSize::Code32) ? static_cast<std::uint8_t>(4) : (switchTempVar_0 == CodeSize::Code16) ? static_cast<std::uint8_t>(2) : static_cast<std::uint8_t>(8);
	}
}
