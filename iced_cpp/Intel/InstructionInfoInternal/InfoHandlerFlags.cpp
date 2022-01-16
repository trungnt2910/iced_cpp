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

#include "InfoHandlerFlags.h"

namespace Iced::Intel::InstructionInfoInternal
{

	std::vector<OpAccess> OpAccesses::Op1 = { OpAccess::None, OpAccess::CondRead, OpAccess::NoMemAccess, OpAccess::Read, OpAccess::Read, OpAccess::ReadWrite, OpAccess::Write };
	std::vector<OpAccess> OpAccesses::Op2 = { OpAccess::None, OpAccess::Read, OpAccess::ReadWrite };
}
