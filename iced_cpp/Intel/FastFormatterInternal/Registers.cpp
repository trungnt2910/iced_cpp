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

using namespace Iced::Intel::FormatterInternal;

#include "../FormatterInternal/RegistersTable.h"

namespace Iced::Intel::FastFormatterInternal
{

	std::vector<FormatterString> Registers::AllRegisters = RegistersTable::GetRegisters();
}
