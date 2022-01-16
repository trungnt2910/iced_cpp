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

using namespace Iced::Intel::FormatterInternal;

namespace Iced::Intel::MasmFormatterInternal
{

	std::vector<FormatterString> Registers::AllRegisters = RegistersTable::GetRegisters();
}
