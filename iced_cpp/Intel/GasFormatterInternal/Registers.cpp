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

#include "Registers.h"
#include "../../NRT_Helpers.h"

#include "../FormatterInternal/RegistersTable.h"

using namespace Iced::Intel::FormatterInternal;

namespace Iced::Intel::GasFormatterInternal
{

	std::vector<FormatterString> Registers::AllRegistersNaked = RegistersTable::GetRegisters();
	std::vector<FormatterString> Registers::AllRegisters = GetRegistersWithPrefix();

	std::vector<FormatterString> Registers::GetRegistersWithPrefix()
	{
		auto registers = AllRegistersNaked;
		System::Diagnostics::Debug2::Assert(!registers.empty());
		auto result = std::vector<FormatterString>(registers.size());
		for (std::int32_t i = 0; i < registers.size(); i++)
		{
			result[i] = FormatterString("%" + registers[i].Get(false));
		}
		return result;
	}
}
