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
#include "../../NRT_Helpers.h"

using namespace Iced::Intel::FormatterInternal;

namespace Iced::Intel::GasFormatterInternal
{

	std::vector<FormatterString> Registers::AllRegistersNaked = RegistersTable::GetRegisters();
	std::vector<FormatterString> Registers::AllRegisters = GetRegistersWithPrefix();

	std::vector<FormatterString> Registers::GetRegistersWithPrefix()
	{
		auto registers = AllRegistersNaked;
		Debug2::Assert(!registers.empty());
		auto result = std::vector<FormatterString>(registers.size());
		for (std::int32_t i = 0; i < registers.size(); i++)
		{
			result[i] = FormatterString("%" + registers[i].Get(false));
		}
		return result;
	}
}
