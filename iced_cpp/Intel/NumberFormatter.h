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

#pragma once

#include "FormatterOptions.h"
#include "IFormatterOptionsProvider.h"
#include <string>
#include <vector>
#include <csharp/exceptionhelper.h>
#include <csharp/stringbuilder.h>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	enum class NumberFormatterFlags
	{
		None = 0,
		AddMinusSign = 0x00000001,
		LeadingZeros = 0x00000002,
		SmallHexNumbersInDecimal = 0x00000004
	};
	DEFINE_FLAGS(NumberFormatterFlags)
		DEFINE_COMP(NumberFormatterFlags)
		DEFINE_ARITH(NumberFormatterFlags)

		/* readonly */
		class NumberFormatter
	{
	private:
		static constexpr std::uint64_t SmallPositiveNumber = 9;
		/* readonly */
		StringBuilder* sb;
	public:
		NumberFormatter(bool dummy);
	private:
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] static void ToHexadecimal(StringBuilder sb, ulong value, int digitGroupSize, string? digitSeparator, int digits, bool upper, bool leadingZero)
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] static void ToHexadecimal(StringBuilder sb, ulong value, int digitGroupSize, string? digitSeparator, int digits, bool upper, bool leadingZero)
		static void ToHexadecimal(StringBuilder* sb, std::uint64_t value, std::int32_t digitGroupSize, const std::string& digitSeparator, std::int32_t digits, bool upper, bool leadingZero);
		static std::vector<std::uint64_t> divs;
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] static void ToDecimal(StringBuilder sb, ulong value, int digitGroupSize, string? digitSeparator, int digits)
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] static void ToDecimal(StringBuilder sb, ulong value, int digitGroupSize, string? digitSeparator, int digits)
		static void ToDecimal(StringBuilder* sb, std::uint64_t value, std::int32_t digitGroupSize, const std::string& digitSeparator, std::int32_t digits);
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] static void ToOctal(StringBuilder sb, ulong value, int digitGroupSize, string? digitSeparator, int digits, string? prefix)
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] static void ToOctal(StringBuilder sb, ulong value, int digitGroupSize, string? digitSeparator, int digits, string? prefix)
		static void ToOctal(StringBuilder* sb, std::uint64_t value, std::int32_t digitGroupSize, const std::string& digitSeparator, std::int32_t digits, const std::string& prefix);
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] static void ToBinary(StringBuilder sb, ulong value, int digitGroupSize, string? digitSeparator, int digits)
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] static void ToBinary(StringBuilder sb, ulong value, int digitGroupSize, string? digitSeparator, int digits)
		static void ToBinary(StringBuilder* sb, std::uint64_t value, std::int32_t digitGroupSize, const std::string& digitSeparator, std::int32_t digits);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] static NumberFormatterFlags GetFlags(bool leadingZeros, bool smallHexNumbersInDecimal)
		static NumberFormatterFlags GetFlags(bool leadingZeros, bool smallHexNumbersInDecimal);
	public:
		std::string FormatInt8(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::int8_t value) const;
		std::string FormatInt16(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::int16_t value) const;
		std::string FormatInt32(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::int32_t value) const;
		std::string FormatInt64(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::int64_t value) const;
		std::string FormatUInt8(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::uint8_t value) const;
		std::string FormatUInt16(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::uint16_t value) const;
		std::string FormatUInt32(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::uint32_t value) const;
		std::string FormatUInt64(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::uint64_t value) const;
		std::string FormatDisplUInt8(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::uint8_t value) const;
		std::string FormatDisplUInt16(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::uint16_t value) const;
		std::string FormatDisplUInt32(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::uint32_t value) const;
		std::string FormatDisplUInt64(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::uint64_t value) const;
		std::string FormatUInt16(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::uint16_t value, bool leadingZeros) const;
		std::string FormatUInt32(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::uint32_t value, bool leadingZeros) const;
		std::string FormatUInt64(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::uint64_t value, bool leadingZeros) const;
	private:
		static std::vector<std::string> smallDecimalValues;
		std::string FormatUnsignedInteger(FormatterOptions* formatterOptions, NumberFormattingOptions const options, std::uint64_t value, std::int32_t valueSize, NumberFormatterFlags flags) const;

		NumberFormatter() = default;
	};
}
