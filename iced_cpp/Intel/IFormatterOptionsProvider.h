// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors


#pragma once

#include "Iced.Intel.Instruction.h"
#include "MemorySizeOptions.g.h"
#include "FormatterOptions.h"
#include "Internal/Enum.h"
#include <string>
#include <limits>

namespace Iced::Intel { class FormatterOperandOptions; }
namespace Iced::Intel { class NumberFormattingOptions; }

namespace Iced::Intel
{
	/// <summary>
	/// Can override options used by a <see cref="Formatter"/>
	/// </summary>
	class IFormatterOptionsProvider
	{
		/// <summary>
		/// Called by the formatter. The method can override any options before the formatter uses them.
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="operand">Operand number, 0-based. This is a formatter operand and isn't necessarily the same as an instruction operand.</param>
		/// <param name="instructionOperand">Instruction operand number, 0-based, or -1 if it's an operand created by the formatter.</param>
		/// <param name="options">Options. Only those options that will be used by the formatter are initialized.</param>
		/// <param name="numberOptions">Number formatting options</param>
	public:
		constexpr virtual void GetOperandOptions(const Instruction& instruction, std::int32_t operand, std::int32_t instructionOperand, FormatterOperandOptions& options, NumberFormattingOptions& numberOptions) = 0;
	};
	/// <summary>
	/// Operand options
	/// </summary>
	class FormatterOperandOptions
	{
	private:
		std::uint32_t flags = 0;
	public:
		enum class Flags : std::uint32_t
		{
			None = 0,
			NoBranchSize = 0x00000001,
			RipRelativeAddresses = 0x00000002,
			MemorySizeShift = 30,
			MemorySizeMask = 3U << static_cast<std::int32_t>(MemorySizeShift)
		};
		ICED_DEFINE_FLAGS_FRIEND(Flags)
		ICED_DEFINE_COMP_FRIEND(Flags)
		ICED_DEFINE_ARITH_FRIEND(Flags)

		/// <summary>
		/// Show branch size (eg. <c>SHORT</c>, <c>NEAR PTR</c>)
		/// </summary>
	public:
		constexpr bool GetBranchSize() const
		{
			return (flags & static_cast<std::uint32_t>(Flags::NoBranchSize)) == 0;
		}
		constexpr void SetBranchSize(bool value)
		{
			if (value)
			{
				flags &= ~static_cast<std::uint32_t>(Flags::NoBranchSize);
			}
			else
			{
				flags |= static_cast<std::uint32_t>(Flags::NoBranchSize);
			}
		}
		/// <summary>
		/// If <see langword="true"/>, show <c>RIP</c> relative addresses as <c>[rip+12345678h]</c>, else show the linear address eg. <c>[1029384756AFBECDh]</c>
		/// </summary>
		constexpr bool GetRipRelativeAddresses() const
		{
			return (flags & static_cast<std::uint32_t>(Flags::RipRelativeAddresses)) != 0;
		}
		constexpr void SetRipRelativeAddresses(bool value)
		{
			if (value)
			{
				flags |= static_cast<std::uint32_t>(Flags::RipRelativeAddresses);
			}
			else
			{
				flags &= ~static_cast<std::uint32_t>(Flags::RipRelativeAddresses);
			}
		}
		/// <summary>
		/// Memory size options
		/// </summary>
		constexpr Iced::Intel::MemorySizeOptions GetMemorySizeOptions()
		{
			return static_cast<Iced::Intel::MemorySizeOptions>(flags >> static_cast<std::int32_t>(Flags::MemorySizeShift));
		}
		constexpr void SetMemorySizeOptions(Iced::Intel::MemorySizeOptions value)
		{
			flags = (flags & ~static_cast<std::uint32_t>(Flags::MemorySizeMask)) | (static_cast<std::uint32_t>(value) << static_cast<std::int32_t>(Flags::MemorySizeShift));
		}
		constexpr FormatterOperandOptions(Flags flags)
		{
			this->flags = static_cast<std::uint32_t>(flags);
		}
		constexpr FormatterOperandOptions(Iced::Intel::MemorySizeOptions options)
		{
			flags = static_cast<std::uint32_t>(options) << static_cast<std::int32_t>(Flags::MemorySizeShift);
		}

		constexpr FormatterOperandOptions() = default;
	};

	/// <summary>
	/// Gets initialized with the default options and can be overridden by a <see cref="IFormatterOptionsProvider"/>
	/// </summary>
	class NumberFormattingOptions
	{
		/// <summary>
		/// Digit separator or <see langword="null"/>/empty string to not use a digit separator
		/// </summary>
	public:
		std::string DigitSeparator;
		/// <summary>
		/// Number prefix or <see langword="null"/>/empty string
		/// </summary>
		std::string Prefix;
		/// <summary>
		/// Number suffix or <see langword="null"/>/empty string
		/// </summary>
		std::string Suffix;
		/// <summary>
		/// Size of a digit group or 0 to not use a digit separator
		/// </summary>
		std::uint8_t DigitGroupSize = 0;
	private:
		std::uint8_t numberBaseByteValue = 0;
		/// <summary>
		/// Use uppercase hex digits
		/// </summary>
	public:
		bool UppercaseHex = false;
		/// <summary>
		/// Small hex numbers (-9 .. 9) are shown in decimal
		/// </summary>
		bool SmallHexNumbersInDecimal = false;
		/// <summary>
		/// Add a leading zero to hex numbers if there's no prefix and the number starts with hex digits <c>A-F</c>
		/// </summary>
		bool AddLeadingZeroToHexNumbers = false;
		/// <summary>
		/// If <see langword="true"/>, add leading zeros to numbers, eg. '1h' vs '00000001h'
		/// </summary>
		bool LeadingZeros = false;
		/// <summary>
		/// If <see langword="true"/>, the number is signed, and if <see langword="false"/> it's an unsigned number
		/// </summary>
		bool SignedNumber = false;
		/// <summary>
		/// Add leading zeros to displacements
		/// </summary>
		bool DisplacementLeadingZeros = false;
		/// <summary>
		/// Number base
		/// </summary>
		constexpr NumberBase GetNumberBase() const
		{
			return static_cast<Iced::Intel::NumberBase>(numberBaseByteValue);
		}
		constexpr void SetNumberBase(NumberBase value)
		{
			numberBaseByteValue = static_cast<std::uint8_t>(value);
		}
		/// <summary>
		/// Creates options used when formatting immediate values
		/// </summary>
		/// <param name="options">Formatter options to use</param>
		/// <returns></returns>
		static constexpr NumberFormattingOptions CreateImmediate(const FormatterOptions& options);
		static constexpr NumberFormattingOptions CreateImmediateInternal(const FormatterOptions& options);
		/// <summary>
		/// Creates options used when formatting displacements
		/// </summary>
		/// <param name="options">Formatter options to use</param>
		/// <returns></returns>
		static constexpr NumberFormattingOptions CreateDisplacement(const FormatterOptions& options);
		static constexpr NumberFormattingOptions CreateDisplacementInternal(const FormatterOptions& options);
		/// <summary>
		/// Creates options used when formatting branch operands
		/// </summary>
		/// <param name="options">Formatter options to use</param>
		/// <returns></returns>
		static constexpr NumberFormattingOptions CreateBranch(const FormatterOptions& options);
		static constexpr NumberFormattingOptions CreateBranchInternal(const FormatterOptions& options);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="options">Formatter options to use</param>
		/// <param name="leadingZeros">Add leading zeros to numbers, eg. <c>1h</c> vs <c>00000001h</c></param>
		/// <param name="signedNumber">Signed numbers if <see langword="true"/>, and unsigned numbers if <see langword="false"/></param>
		/// <param name="displacementLeadingZeros">Add leading zeros to displacements</param>
		constexpr NumberFormattingOptions(const FormatterOptions& options, bool leadingZeros, bool signedNumber, bool displacementLeadingZeros);

		constexpr NumberFormattingOptions() = default;
	};

	constexpr NumberFormattingOptions NumberFormattingOptions::CreateImmediate(const FormatterOptions& options)
	{
		return CreateImmediateInternal(options);
	}

	constexpr NumberFormattingOptions NumberFormattingOptions::CreateImmediateInternal(const FormatterOptions& options)
	{
		return NumberFormattingOptions(options, options.GetLeadingZeros(), options.GetSignedImmediateOperands(), false);
	}

	constexpr NumberFormattingOptions NumberFormattingOptions::CreateDisplacement(const FormatterOptions& options)
	{
		return CreateDisplacementInternal(options);
	}

	constexpr NumberFormattingOptions NumberFormattingOptions::CreateDisplacementInternal(const FormatterOptions& options)
	{
		return NumberFormattingOptions(options, options.GetLeadingZeros(), options.GetSignedMemoryDisplacements(), options.GetDisplacementLeadingZeros());
	}

	constexpr NumberFormattingOptions NumberFormattingOptions::CreateBranch(const FormatterOptions& options)
	{
		return CreateBranchInternal(options);
	}

	constexpr NumberFormattingOptions NumberFormattingOptions::CreateBranchInternal(const FormatterOptions& options)
	{
		return NumberFormattingOptions(options, options.GetBranchLeadingZeros(), false, false);
	}

	constexpr NumberFormattingOptions::NumberFormattingOptions(const FormatterOptions& options, bool leadingZeros, bool signedNumber, bool displacementLeadingZeros)
	{
		LeadingZeros = leadingZeros;
		SignedNumber = signedNumber;
		DisplacementLeadingZeros = displacementLeadingZeros;
		numberBaseByteValue = static_cast<std::uint8_t>(options.GetNumberBase());
		DigitSeparator = options.GetDigitSeparator();
		UppercaseHex = options.GetUppercaseHex();
		SmallHexNumbersInDecimal = options.GetSmallHexNumbersInDecimal();
		AddLeadingZeroToHexNumbers = options.GetAddLeadingZeroToHexNumbers();
		std::int32_t digitGroupSize;
		switch (options.GetNumberBase())
		{
		case NumberBase::Hexadecimal:
			Prefix = options.GetHexPrefix();
			Suffix = options.GetHexSuffix();
			digitGroupSize = options.GetHexDigitGroupSize();
			break;
		case NumberBase::Decimal:
			Prefix = options.GetDecimalPrefix();
			Suffix = options.GetDecimalSuffix();
			digitGroupSize = options.GetDecimalDigitGroupSize();
			break;
		case NumberBase::Octal:
			Prefix = options.GetOctalPrefix();
			Suffix = options.GetOctalSuffix();
			digitGroupSize = options.GetOctalDigitGroupSize();
			break;
		case NumberBase::Binary:
			Prefix = options.GetBinaryPrefix();
			Suffix = options.GetBinarySuffix();
			digitGroupSize = options.GetBinaryDigitGroupSize();
			break;
		default:
			throw std::runtime_error("invalid operation");
		}
		if (digitGroupSize < 0)
		{
			DigitGroupSize = 0;
		}
		else if (digitGroupSize > std::numeric_limits<std::uint8_t>::max())
		{
			DigitGroupSize = std::numeric_limits<std::uint8_t>::max();
		}
		else
		{
			DigitGroupSize = static_cast<std::uint8_t>(digitGroupSize);
		}
	}

}
