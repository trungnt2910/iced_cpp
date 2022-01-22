// C# helper headers
#include <csharp/classes.h>
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

#include "../FormatterInternal/RegistersTable.h"

using namespace Iced::Intel::FormatterInternal;

namespace Iced::Intel::IntelFormatterInternal
{

	std::vector<FormatterString> Registers::AllRegisters = RegistersTable::GetRegisters();
}
