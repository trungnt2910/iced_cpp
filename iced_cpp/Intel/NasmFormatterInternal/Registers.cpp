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

#include "Registers.h"
#include "../FormatterInternal/RegistersTable.h"
#include "../Register.g.h"

using namespace Iced::Intel::FormatterInternal;

namespace Iced::Intel::NasmFormatterInternal
{

	std::vector<FormatterString> Registers::AllRegisters = GetRegisters();

	std::vector<FormatterString> Registers::GetRegisters()
	{
		auto registers = RegistersTable::GetRegisters();
		for (std::int32_t i = 0; i < 8; i++)
		{
			registers[static_cast<std::int32_t>(Register::ST0) + i] = FormatterString("st" + std::to_string(i));
		}
		return registers;
	}
}
