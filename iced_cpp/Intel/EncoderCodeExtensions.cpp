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

#include "EncoderCodeExtensions.h"
#include "EncoderInternal/OpCodeInfos.h"
#include "ThrowHelper.h"

using namespace Iced::Intel::EncoderInternal;

namespace Iced::Intel
{

	OpCodeInfo* EncoderCodeExtensions::ToOpCode(Code code)
	{
		auto infos = OpCodeInfos::Infos;
		if (static_cast<std::uint32_t>(code) >= static_cast<std::uint32_t>(infos.size()))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_code();
		}
		return infos[static_cast<std::int32_t>(code)];
	}
}
