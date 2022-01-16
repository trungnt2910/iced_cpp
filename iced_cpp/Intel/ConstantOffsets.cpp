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

#include "ConstantOffsets.h"

namespace Iced::Intel
{

	bool ConstantOffsets::GetHasDisplacement() const
	{
		return DisplacementSize != 0;
	}

	bool ConstantOffsets::GetHasImmediate() const
	{
		return ImmediateSize != 0;
	}

	bool ConstantOffsets::GetHasImmediate2() const
	{
		return ImmediateSize2 != 0;
	}
}
