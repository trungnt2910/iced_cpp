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

#include "NumberFormatter.h"
#include "../NRT_Helpers.h"

namespace Iced::Intel
{

	NumberFormatter::NumberFormatter(bool dummy)
	{
		constexpr std::int32_t CAP = 2 + 64 + (16 - 1); // # digit separators if group size == 4 and digit sep is one char
		sb = new StringBuilder(CAP);
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] static void ToHexadecimal(StringBuilder sb, ulong value, int digitGroupSize, string? digitSeparator, int digits, bool upper, bool leadingZero)
	void NumberFormatter::ToHexadecimal(StringBuilder* sb, std::uint64_t value, std::int32_t digitGroupSize, const std::string& digitSeparator, std::int32_t digits, bool upper, bool leadingZero)
	{
		if (digits == 0)
		{
			digits = 1;
			for (std::uint64_t tmp = value; ;)
			{
				tmp >>= 4;
				if (tmp == 0)
				{
					break;
				}
				digits++;
			}
		}
		std::int32_t hexHigh = upper ? 'A' - 10 : 'a' - 10;
		if (leadingZero && digits < 17 && static_cast<std::int32_t>((value >> ((digits - 1) << 2)) & 0xF) > 9)
		{
			digits++; // Another 0
		}
		bool useDigitSep = digitGroupSize > 0 && !digitSeparator.empty();
		for (std::int32_t i = 0; i < digits; i++)
		{
			std::int32_t index = digits - i - 1;
			std::int32_t digit = index >= 16 ? 0 : static_cast<std::int32_t>((value >> (index << 2)) & 0xF);
			if (digit > 9)
			{
				sb->append(static_cast<char>(digit + hexHigh));
			}
			else
			{
				sb->append(static_cast<char>(digit + '0'));
			}
			if (useDigitSep && index > 0 && (index % digitGroupSize) == 0)
			{
				//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
				//ORIGINAL LINE: sb.Append(digitSeparator!);
				sb->append(digitSeparator);
			}
		}
	}

	std::vector<std::uint64_t> NumberFormatter::divs = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000, 100000000000000, 1000000000000000, 10000000000000000, 100000000000000000, 1000000000000000000, 10000000000000000000 };

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] static void ToDecimal(StringBuilder sb, ulong value, int digitGroupSize, string? digitSeparator, int digits)
	void NumberFormatter::ToDecimal(StringBuilder* sb, std::uint64_t value, std::int32_t digitGroupSize, const std::string& digitSeparator, std::int32_t digits)
	{
		if (digits == 0)
		{
			digits = 1;
			for (std::uint64_t tmp = value; ;)
			{
				tmp /= 10;
				if (tmp == 0)
				{
					break;
				}
				digits++;
			}
		}
		bool useDigitSep = digitGroupSize > 0 && !System::string2::IsNullOrEmpty(digitSeparator);
		auto divs = NumberFormatter::divs;
		for (std::int32_t i = 0; i < digits; i++)
		{
			std::int32_t index = digits - i - 1;
			if (static_cast<std::uint32_t>(index) < static_cast<std::uint32_t>(divs.size()))
			{
				std::int32_t digit = static_cast<std::int32_t>(value / divs[index] % 10);
				sb->append(static_cast<char>(digit + '0'));
			}
			else
			{
				sb->append('0');
			}
			if (useDigitSep && index > 0 && (index % digitGroupSize) == 0)
			{
				//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
				//ORIGINAL LINE: sb.Append(digitSeparator!);
				sb->append(digitSeparator);
			}
		}
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] static void ToOctal(StringBuilder sb, ulong value, int digitGroupSize, string? digitSeparator, int digits, string? prefix)
	void NumberFormatter::ToOctal(StringBuilder* sb, std::uint64_t value, std::int32_t digitGroupSize, const std::string& digitSeparator, std::int32_t digits, const std::string& prefix)
	{
		if (digits == 0)
		{
			digits = 1;
			for (std::uint64_t tmp = value; ;)
			{
				tmp >>= 3;
				if (tmp == 0)
				{
					break;
				}
				digits++;
			}
		}
		if (!prefix.empty())
		{
			// The prefix is part of the number so that a digit separator can be placed
			// between the "prefix" and the rest of the number, eg. "0" + "1234" with
			// digit separator "`" and group size = 2 is "0`12`34" and not "012`34".
			// Other prefixes, eg. "0o" prefix: 0o12`34 and never 0o`12`34.
			if (prefix == "0")
			{
				if (digits < 23 && static_cast<std::int32_t>((value >> (digits - 1) * 3) & 7) != 0)
				{
					digits++; // Another 0
				}
			}
			else
			{
				sb->append(prefix);
			}
		}
		bool useDigitSep = digitGroupSize > 0 && !System::string2::IsNullOrEmpty(digitSeparator);
		for (std::int32_t i = 0; i < digits; i++)
		{
			std::int32_t index = digits - i - 1;
			std::int32_t digit = index >= 22 ? 0 : static_cast<std::int32_t>((value >> index * 3) & 7);
			sb->append(static_cast<char>(digit + '0'));
			if (useDigitSep && index > 0 && (index % digitGroupSize) == 0)
			{
				//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
				//ORIGINAL LINE: sb.Append(digitSeparator!);
				sb->append(digitSeparator);
			}
		}
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] static void ToBinary(StringBuilder sb, ulong value, int digitGroupSize, string? digitSeparator, int digits)
	void NumberFormatter::ToBinary(StringBuilder* sb, std::uint64_t value, std::int32_t digitGroupSize, const std::string& digitSeparator, std::int32_t digits)
	{
		if (digits == 0)
		{
			digits = 1;
			for (std::uint64_t tmp = value; ;)
			{
				tmp >>= 1;
				if (tmp == 0)
				{
					break;
				}
				digits++;
			}
		}
		bool useDigitSep = digitGroupSize > 0 && !System::string2::IsNullOrEmpty(digitSeparator);
		for (std::int32_t i = 0; i < digits; i++)
		{
			std::int32_t index = digits - i - 1;
			std::int32_t digit = index >= 64 ? 0 : static_cast<std::int32_t>((value >> index) & 1);
			sb->append(static_cast<char>(digit + '0'));
			if (useDigitSep && index > 0 && (index % digitGroupSize) == 0)
			{
				//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
				//ORIGINAL LINE: sb.Append(digitSeparator!);
				sb->append(digitSeparator);
			}
		}
	}

	NumberFormatterFlags NumberFormatter::GetFlags(bool leadingZeros, bool smallHexNumbersInDecimal)
	{
		auto flags = NumberFormatterFlags::None;
		if (leadingZeros)
		{
			flags |= NumberFormatterFlags::LeadingZeros;
		}
		if (smallHexNumbersInDecimal)
		{
			flags |= NumberFormatterFlags::SmallHexNumbersInDecimal;
		}
		return flags;
	}

	std::string NumberFormatter::FormatInt8(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::int8_t value) const
	{
		auto flags = GetFlags(options.LeadingZeros, options.SmallHexNumbersInDecimal);
		if (value < 0)
		{
			flags |= NumberFormatterFlags::AddMinusSign;
			value = static_cast<std::int8_t>(-value);
		}
		return FormatUnsignedInteger(formatterOptions, options, static_cast<std::uint8_t>(value), 8, flags);
	}

	std::string NumberFormatter::FormatInt16(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::int16_t value) const
	{
		auto flags = GetFlags(options.LeadingZeros, options.SmallHexNumbersInDecimal);
		if (value < 0)
		{
			flags |= NumberFormatterFlags::AddMinusSign;
			value = static_cast<std::int16_t>(-value);
		}
		return FormatUnsignedInteger(formatterOptions, options, static_cast<std::uint16_t>(value), 16, flags);
	}

	std::string NumberFormatter::FormatInt32(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::int32_t value) const
	{
		auto flags = GetFlags(options.LeadingZeros, options.SmallHexNumbersInDecimal);
		if (value < 0)
		{
			flags |= NumberFormatterFlags::AddMinusSign;
			value = -value;
		}
		return FormatUnsignedInteger(formatterOptions, options, static_cast<std::uint32_t>(value), 32, flags);
	}

	std::string NumberFormatter::FormatInt64(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::int64_t value) const
	{
		auto flags = GetFlags(options.LeadingZeros, options.SmallHexNumbersInDecimal);
		if (value < 0)
		{
			flags |= NumberFormatterFlags::AddMinusSign;
			value = -value;
		}
		return FormatUnsignedInteger(formatterOptions, options, static_cast<std::uint64_t>(value), 64, flags);
	}

	std::string NumberFormatter::FormatUInt8(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::uint8_t value) const
	{
		return FormatUnsignedInteger(formatterOptions, options, value, 8, GetFlags(options.LeadingZeros, options.SmallHexNumbersInDecimal));
	}

	std::string NumberFormatter::FormatUInt16(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::uint16_t value) const
	{
		return FormatUnsignedInteger(formatterOptions, options, value, 16, GetFlags(options.LeadingZeros, options.SmallHexNumbersInDecimal));
	}

	std::string NumberFormatter::FormatUInt32(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::uint32_t value) const
	{
		return FormatUnsignedInteger(formatterOptions, options, value, 32, GetFlags(options.LeadingZeros, options.SmallHexNumbersInDecimal));
	}

	std::string NumberFormatter::FormatUInt64(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::uint64_t value) const
	{
		return FormatUnsignedInteger(formatterOptions, options, value, 64, GetFlags(options.LeadingZeros, options.SmallHexNumbersInDecimal));
	}

	std::string NumberFormatter::FormatDisplUInt8(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::uint8_t value) const
	{
		return FormatUnsignedInteger(formatterOptions, options, value, 8, GetFlags(options.DisplacementLeadingZeros, options.SmallHexNumbersInDecimal));
	}

	std::string NumberFormatter::FormatDisplUInt16(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::uint16_t value) const
	{
		return FormatUnsignedInteger(formatterOptions, options, value, 16, GetFlags(options.DisplacementLeadingZeros, options.SmallHexNumbersInDecimal));
	}

	std::string NumberFormatter::FormatDisplUInt32(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::uint32_t value) const
	{
		return FormatUnsignedInteger(formatterOptions, options, value, 32, GetFlags(options.DisplacementLeadingZeros, options.SmallHexNumbersInDecimal));
	}

	std::string NumberFormatter::FormatDisplUInt64(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::uint64_t value) const
	{
		return FormatUnsignedInteger(formatterOptions, options, value, 64, GetFlags(options.DisplacementLeadingZeros, options.SmallHexNumbersInDecimal));
	}

	std::string NumberFormatter::FormatUInt16(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::uint16_t value, bool leadingZeros) const
	{
		return FormatUnsignedInteger(formatterOptions, options, value, 16, GetFlags(leadingZeros, options.SmallHexNumbersInDecimal));
	}

	std::string NumberFormatter::FormatUInt32(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::uint32_t value, bool leadingZeros) const
	{
		return FormatUnsignedInteger(formatterOptions, options, value, 32, GetFlags(leadingZeros, options.SmallHexNumbersInDecimal));
	}

	std::string NumberFormatter::FormatUInt64(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::uint64_t value, bool leadingZeros) const
	{
		return FormatUnsignedInteger(formatterOptions, options, value, 64, GetFlags(leadingZeros, options.SmallHexNumbersInDecimal));
	}

	std::vector<std::string> NumberFormatter::smallDecimalValues = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

	std::string NumberFormatter::FormatUnsignedInteger(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::uint64_t value, std::int32_t valueSize, NumberFormatterFlags flags) const
	{
		sb->clear();
		if ((flags & NumberFormatterFlags::AddMinusSign) != 0)
		{
			sb->append('-');
		}
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: string? suffix;
		std::string suffix;
		switch (options.GetNumberBase())
		{
		case NumberBase::Hexadecimal:
			if ((flags & NumberFormatterFlags::SmallHexNumbersInDecimal) != 0 && value <= SmallPositiveNumber)
			{
				if (formatterOptions->GetDecimalPrefix().empty() && formatterOptions->GetDecimalSuffix().empty())
				{
					return smallDecimalValues[static_cast<std::int32_t>(value)];
				}
				if (!formatterOptions->GetDecimalPrefix().empty())
				{
					sb->append(formatterOptions->GetDecimalPrefix());
				}
				sb->append(smallDecimalValues[static_cast<std::int32_t>(value)]);
				suffix = formatterOptions->GetDecimalSuffix();
			}
			else
			{
				if (!options.Prefix.empty())
				{
					sb->append(options.Prefix);
				}
				ToHexadecimal(sb, value, options.DigitGroupSize, options.DigitSeparator, (flags & NumberFormatterFlags::LeadingZeros) != 0 ? (valueSize + 3) >> 2 : 0, options.UppercaseHex, options.AddLeadingZeroToHexNumbers && options.Prefix.empty());
				suffix = options.Suffix;
			}
			break;
		case NumberBase::Decimal:
			if (!options.Prefix.empty())
			{
				sb->append(options.Prefix);
			}
			ToDecimal(sb, value, options.DigitGroupSize, options.DigitSeparator, 0);
			suffix = options.Suffix;
			break;
		case NumberBase::Octal:
			ToOctal(sb, value, options.DigitGroupSize, options.DigitSeparator, (flags & NumberFormatterFlags::LeadingZeros) != 0 ? (valueSize + 2) / 3 : 0, options.Prefix);
			suffix = options.Suffix;
			break;
		case NumberBase::Binary:
			if (!options.Prefix.empty())
			{
				sb->append(options.Prefix);
			}
			ToBinary(sb, value, options.DigitGroupSize, options.DigitSeparator, (flags & NumberFormatterFlags::LeadingZeros) != 0 ? valueSize : 0);
			suffix = options.Suffix;
			break;
		default:
			throw InvalidOperationException();
		}
		if (!suffix.empty())
		{
			sb->append(suffix);
		}
		return sb->toString();
	}
}
