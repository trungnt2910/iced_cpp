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

#include "MnemonicUtils.h"
#include "MnemonicUtilsData.g.h"

namespace Iced::Intel
{

	Iced::Intel::Mnemonic MnemonicUtils::Mnemonic(Code code)
	{
		assert(static_cast<std::uint32_t>(code) < static_cast<std::uint32_t>(MnemonicUtilsData::toMnemonic.size()));
		return static_cast<Iced::Intel::Mnemonic>(MnemonicUtilsData::toMnemonic[static_cast<std::int32_t>(code)]);
	}
}
