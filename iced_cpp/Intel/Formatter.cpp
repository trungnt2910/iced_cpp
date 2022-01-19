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

#include "Formatter.h"

namespace Iced::Intel
{

	void Formatter::FormatMnemonic(const Instruction& instruction, FormatterOutput* output)
	{
		FormatMnemonic(instruction, output, FormatMnemonicOptions::None);
	}

	std::string Formatter::FormatInt8(std::int8_t value)
	{
		return FormatInt8(value, NumberFormattingOptions::CreateImmediateInternal(GetOptions()));
	}

	std::string Formatter::FormatInt16(std::int16_t value)
	{
		return FormatInt16(value, NumberFormattingOptions::CreateImmediateInternal(GetOptions()));
	}

	std::string Formatter::FormatInt32(std::int32_t value)
	{
		return FormatInt32(value, NumberFormattingOptions::CreateImmediateInternal(GetOptions()));
	}

	std::string Formatter::FormatInt64(std::int64_t value)
	{
		return FormatInt64(value, NumberFormattingOptions::CreateImmediateInternal(GetOptions()));
	}

	std::string Formatter::FormatUInt8(std::uint8_t value)
	{
		return FormatUInt8(value, NumberFormattingOptions::CreateImmediateInternal(GetOptions()));
	}

	std::string Formatter::FormatUInt16(std::uint16_t value)
	{
		return FormatUInt16(value, NumberFormattingOptions::CreateImmediateInternal(GetOptions()));
	}

	std::string Formatter::FormatUInt32(std::uint32_t value)
	{
		return FormatUInt32(value, NumberFormattingOptions::CreateImmediateInternal(GetOptions()));
	}

	std::string Formatter::FormatUInt64(std::uint64_t value)
	{
		return FormatUInt64(value, NumberFormattingOptions::CreateImmediateInternal(GetOptions()));
	}
}
