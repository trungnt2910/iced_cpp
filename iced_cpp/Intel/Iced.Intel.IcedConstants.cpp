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

#include "Iced.Intel.IcedConstants.h"

namespace Iced::Intel
{

	bool IcedConstants::IsMvex(Code code)
	{
		return (static_cast<std::uint32_t>(code) - MvexStart) < MvexLength;
	}
}