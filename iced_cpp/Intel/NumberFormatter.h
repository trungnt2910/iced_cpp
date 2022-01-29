// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include "FormatterOptions.h"
#include "IFormatterOptionsProvider.h"
#include "Internal/Enum.h"
#include <array>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>


namespace Iced::Intel
{
	enum class NumberFormatterFlags
	{
		None = 0,
		AddMinusSign = 0x00000001,
		LeadingZeros = 0x00000002,
		SmallHexNumbersInDecimal = 0x00000004
	};
	ICED_DEFINE_FLAGS(NumberFormatterFlags)
	ICED_DEFINE_COMP(NumberFormatterFlags)
	ICED_DEFINE_ARITH(NumberFormatterFlags)

	class NumberFormatter
	{
	private:
		static constexpr std::uint64_t SmallPositiveNumber = 9;
		/* readonly */
		// System.Text.StringBuidler and std::string have the same efficiency.
		mutable std::string sb;
	public:
		constexpr NumberFormatter(bool dummy);
	private:
		constexpr static void ToHexadecimal(std::string& sb, std::uint64_t value, std::int32_t digitGroupSize, const std::string& digitSeparator, std::int32_t digits, bool upper, bool leadingZero);
		inline static constexpr std::array divs = std::to_array<std::uint64_t>({ 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000, 100000000000000, 1000000000000000, 10000000000000000, 100000000000000000, 1000000000000000000, 10000000000000000000 });
		constexpr static void ToDecimal(std::string& sb, std::uint64_t value, std::int32_t digitGroupSize, const std::string& digitSeparator, std::int32_t digits);
		constexpr static void ToOctal(std::string& sb, std::uint64_t value, std::int32_t digitGroupSize, const std::string& digitSeparator, std::int32_t digits, const std::string& prefix);
		constexpr static void ToBinary(std::string& sb, std::uint64_t value, std::int32_t digitGroupSize, const std::string& digitSeparator, std::int32_t digits);
		constexpr static NumberFormatterFlags GetFlags(bool leadingZeros, bool smallHexNumbersInDecimal);
	public:
		constexpr std::string FormatInt8(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::int8_t value) const;
		constexpr std::string FormatInt16(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::int16_t value) const;
		constexpr std::string FormatInt32(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::int32_t value) const;
		constexpr std::string FormatInt64(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::int64_t value) const;
		constexpr std::string FormatUInt8(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::uint8_t value) const;
		constexpr std::string FormatUInt16(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::uint16_t value) const;
		constexpr std::string FormatUInt32(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::uint32_t value) const;
		constexpr std::string FormatUInt64(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::uint64_t value) const;
		constexpr std::string FormatDisplUInt8(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::uint8_t value) const;
		constexpr std::string FormatDisplUInt16(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::uint16_t value) const;
		constexpr std::string FormatDisplUInt32(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::uint32_t value) const;
		constexpr std::string FormatDisplUInt64(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::uint64_t value) const;
		constexpr std::string FormatUInt16(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::uint16_t value, bool leadingZeros) const;
		constexpr std::string FormatUInt32(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::uint32_t value, bool leadingZeros) const;
		constexpr std::string FormatUInt64(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::uint64_t value, bool leadingZeros) const;
	private:
		inline static constexpr std::array smallDecimalValues = std::to_array<std::string_view>({ "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" });
		constexpr std::string FormatUnsignedInteger(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::uint64_t value, std::int32_t valueSize, NumberFormatterFlags flags) const;

		constexpr NumberFormatter() = default;
	};

	constexpr NumberFormatter::NumberFormatter(bool dummy)
	{
		constexpr std::int32_t CAP = 2 + 64 + (16 - 1); // # digit separators if group size == 4 and digit sep is one char
		sb.reserve(CAP);
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] constexpr static void ToHexadecimal(StringBuilder sb, ulong value, int digitGroupSize, string? digitSeparator, int digits, bool upper, bool leadingZero)
	constexpr void NumberFormatter::ToHexadecimal(std::string& sb, std::uint64_t value, std::int32_t digitGroupSize, const std::string& digitSeparator, std::int32_t digits, bool upper, bool leadingZero)
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
				sb.push_back(static_cast<char>(digit + hexHigh));
			}
			else
			{
				sb.push_back(static_cast<char>(digit + '0'));
			}
			if (useDigitSep && index > 0 && (index % digitGroupSize) == 0)
			{
				sb.append(digitSeparator);
			}
		}
	}

	constexpr void NumberFormatter::ToDecimal(std::string& sb, std::uint64_t value, std::int32_t digitGroupSize, const std::string& digitSeparator, std::int32_t digits)
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
		bool useDigitSep = digitGroupSize > 0 && !digitSeparator.empty();
		auto divs = NumberFormatter::divs;
		for (std::int32_t i = 0; i < digits; i++)
		{
			std::int32_t index = digits - i - 1;
			if (static_cast<std::uint32_t>(index) < static_cast<std::uint32_t>(divs.size()))
			{
				std::int32_t digit = static_cast<std::int32_t>(value / divs[index] % 10);
				sb.push_back(static_cast<char>(digit + '0'));
			}
			else
			{
				sb.push_back('0');
			}
			if (useDigitSep && index > 0 && (index % digitGroupSize) == 0)
			{
				sb.append(digitSeparator);
			}
		}
	}

	constexpr void NumberFormatter::ToOctal(std::string& sb, std::uint64_t value, std::int32_t digitGroupSize, const std::string& digitSeparator, std::int32_t digits, const std::string& prefix)
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
				sb.append(prefix);
			}
		}
		bool useDigitSep = digitGroupSize > 0 && !digitSeparator.empty();
		for (std::int32_t i = 0; i < digits; i++)
		{
			std::int32_t index = digits - i - 1;
			std::int32_t digit = index >= 22 ? 0 : static_cast<std::int32_t>((value >> index * 3) & 7);
			sb.push_back(static_cast<char>(digit + '0'));
			if (useDigitSep && index > 0 && (index % digitGroupSize) == 0)
			{
				sb.append(digitSeparator);
			}
		}
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] constexpr static void ToBinary(StringBuilder sb, ulong value, int digitGroupSize, string? digitSeparator, int digits)
	constexpr void NumberFormatter::ToBinary(std::string& sb, std::uint64_t value, std::int32_t digitGroupSize, const std::string& digitSeparator, std::int32_t digits)
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
		bool useDigitSep = digitGroupSize > 0 && !digitSeparator.empty();
		for (std::int32_t i = 0; i < digits; i++)
		{
			std::int32_t index = digits - i - 1;
			std::int32_t digit = index >= 64 ? 0 : static_cast<std::int32_t>((value >> index) & 1);
			sb.push_back(static_cast<char>(digit + '0'));
			if (useDigitSep && index > 0 && (index % digitGroupSize) == 0)
			{
				//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
				//ORIGINAL LINE: sb.Append(digitSeparator!);
				sb.append(digitSeparator);
			}
		}
	}

	constexpr NumberFormatterFlags NumberFormatter::GetFlags(bool leadingZeros, bool smallHexNumbersInDecimal)
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

	constexpr std::string NumberFormatter::FormatInt8(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::int8_t value) const
	{
		auto flags = GetFlags(options.LeadingZeros, options.SmallHexNumbersInDecimal);
		if (value < 0)
		{
			flags |= NumberFormatterFlags::AddMinusSign;
			value = static_cast<std::int8_t>(-value);
		}
		return FormatUnsignedInteger(formatterOptions, options, static_cast<std::uint8_t>(value), 8, flags);
	}

	constexpr std::string NumberFormatter::FormatInt16(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::int16_t value) const
	{
		auto flags = GetFlags(options.LeadingZeros, options.SmallHexNumbersInDecimal);
		if (value < 0)
		{
			flags |= NumberFormatterFlags::AddMinusSign;
			value = static_cast<std::int16_t>(-value);
		}
		return FormatUnsignedInteger(formatterOptions, options, static_cast<std::uint16_t>(value), 16, flags);
	}

	constexpr std::string NumberFormatter::FormatInt32(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::int32_t value) const
	{
		auto flags = GetFlags(options.LeadingZeros, options.SmallHexNumbersInDecimal);
		if (value < 0)
		{
			flags |= NumberFormatterFlags::AddMinusSign;
			value = -value;
		}
		return FormatUnsignedInteger(formatterOptions, options, static_cast<std::uint32_t>(value), 32, flags);
	}

	constexpr std::string NumberFormatter::FormatInt64(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::int64_t value) const
	{
		auto flags = GetFlags(options.LeadingZeros, options.SmallHexNumbersInDecimal);
		if (value < 0)
		{
			flags |= NumberFormatterFlags::AddMinusSign;
			value = -value;
		}
		return FormatUnsignedInteger(formatterOptions, options, static_cast<std::uint64_t>(value), 64, flags);
	}

	constexpr std::string NumberFormatter::FormatUInt8(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::uint8_t value) const
	{
		return FormatUnsignedInteger(formatterOptions, options, value, 8, GetFlags(options.LeadingZeros, options.SmallHexNumbersInDecimal));
	}

	constexpr std::string NumberFormatter::FormatUInt16(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::uint16_t value) const
	{
		return FormatUnsignedInteger(formatterOptions, options, value, 16, GetFlags(options.LeadingZeros, options.SmallHexNumbersInDecimal));
	}

	constexpr std::string NumberFormatter::FormatUInt32(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::uint32_t value) const
	{
		return FormatUnsignedInteger(formatterOptions, options, value, 32, GetFlags(options.LeadingZeros, options.SmallHexNumbersInDecimal));
	}

	constexpr std::string NumberFormatter::FormatUInt64(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::uint64_t value) const
	{
		return FormatUnsignedInteger(formatterOptions, options, value, 64, GetFlags(options.LeadingZeros, options.SmallHexNumbersInDecimal));
	}

	constexpr std::string NumberFormatter::FormatDisplUInt8(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::uint8_t value) const
	{
		return FormatUnsignedInteger(formatterOptions, options, value, 8, GetFlags(options.DisplacementLeadingZeros, options.SmallHexNumbersInDecimal));
	}

	constexpr std::string NumberFormatter::FormatDisplUInt16(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::uint16_t value) const
	{
		return FormatUnsignedInteger(formatterOptions, options, value, 16, GetFlags(options.DisplacementLeadingZeros, options.SmallHexNumbersInDecimal));
	}

	constexpr std::string NumberFormatter::FormatDisplUInt32(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::uint32_t value) const
	{
		return FormatUnsignedInteger(formatterOptions, options, value, 32, GetFlags(options.DisplacementLeadingZeros, options.SmallHexNumbersInDecimal));
	}

	constexpr std::string NumberFormatter::FormatDisplUInt64(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::uint64_t value) const
	{
		return FormatUnsignedInteger(formatterOptions, options, value, 64, GetFlags(options.DisplacementLeadingZeros, options.SmallHexNumbersInDecimal));
	}

	constexpr std::string NumberFormatter::FormatUInt16(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::uint16_t value, bool leadingZeros) const
	{
		return FormatUnsignedInteger(formatterOptions, options, value, 16, GetFlags(leadingZeros, options.SmallHexNumbersInDecimal));
	}

	constexpr std::string NumberFormatter::FormatUInt32(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::uint32_t value, bool leadingZeros) const
	{
		return FormatUnsignedInteger(formatterOptions, options, value, 32, GetFlags(leadingZeros, options.SmallHexNumbersInDecimal));
	}

	constexpr std::string NumberFormatter::FormatUInt64(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::uint64_t value, bool leadingZeros) const
	{
		return FormatUnsignedInteger(formatterOptions, options, value, 64, GetFlags(leadingZeros, options.SmallHexNumbersInDecimal));
	}
	
	constexpr std::string NumberFormatter::FormatUnsignedInteger(const FormatterOptions& formatterOptions, const NumberFormattingOptions& options, std::uint64_t value, std::int32_t valueSize, NumberFormatterFlags flags) const
	{
		sb.clear();
		if ((flags & NumberFormatterFlags::AddMinusSign) != 0)
		{
			sb.push_back('-');
		}
		std::string suffix;
		switch (options.GetNumberBase())
		{
		case NumberBase::Hexadecimal:
			if ((flags & NumberFormatterFlags::SmallHexNumbersInDecimal) != 0 && value <= SmallPositiveNumber)
			{
				if (formatterOptions.GetDecimalPrefix().empty() && formatterOptions.GetDecimalSuffix().empty())
				{
					return (std::string)smallDecimalValues[static_cast<std::int32_t>(value)];
				}
				if (!formatterOptions.GetDecimalPrefix().empty())
				{
					sb.append(formatterOptions.GetDecimalPrefix());
				}
				sb.append(smallDecimalValues[static_cast<std::int32_t>(value)]);
				suffix = formatterOptions.GetDecimalSuffix();
			}
			else
			{
				if (!options.Prefix.empty())
				{
					sb.append(options.Prefix);
				}
				ToHexadecimal(sb, value, options.DigitGroupSize, options.DigitSeparator, (flags & NumberFormatterFlags::LeadingZeros) != 0 ? (valueSize + 3) >> 2 : 0, options.UppercaseHex, options.AddLeadingZeroToHexNumbers && options.Prefix.empty());
				suffix = options.Suffix;
			}
			break;
		case NumberBase::Decimal:
			if (!options.Prefix.empty())
			{
				sb.append(options.Prefix);
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
				sb.append(options.Prefix);
			}
			ToBinary(sb, value, options.DigitGroupSize, options.DigitSeparator, (flags & NumberFormatterFlags::LeadingZeros) != 0 ? valueSize : 0);
			suffix = options.Suffix;
			break;
		default:
			throw std::runtime_error("unexpected number base.");
		}
		if (!suffix.empty())
		{
			sb.append(suffix);
		}
		return sb;
	}
}
