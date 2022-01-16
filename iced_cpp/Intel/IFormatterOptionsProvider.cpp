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

#include "IFormatterOptionsProvider.h"
#include "ThrowHelper.h"

namespace Iced::Intel
{

	bool FormatterOperandOptions::GetBranchSize() const
	{
		return (flags & static_cast<std::uint32_t>(Flags::NoBranchSize)) == 0;
	}

	void FormatterOperandOptions::SetBranchSize(bool value)
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

	bool FormatterOperandOptions::GetRipRelativeAddresses() const
	{
		return (flags & static_cast<std::uint32_t>(Flags::RipRelativeAddresses)) != 0;
	}

	void FormatterOperandOptions::SetRipRelativeAddresses(bool value)
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

	Iced::Intel::MemorySizeOptions FormatterOperandOptions::GetMemorySizeOptions() const
	{
		return static_cast<Iced::Intel::MemorySizeOptions>(flags >> static_cast<std::int32_t>(Flags::MemorySizeShift));
	}

	void FormatterOperandOptions::SetMemorySizeOptions(Iced::Intel::MemorySizeOptions value)
	{
		flags = (flags & ~static_cast<std::uint32_t>(Flags::MemorySizeMask)) | (static_cast<std::uint32_t>(value) << static_cast<std::int32_t>(Flags::MemorySizeShift));
	}

	FormatterOperandOptions::FormatterOperandOptions(Flags flags)
	{
		this->flags = static_cast<std::uint32_t>(flags);
	}

	FormatterOperandOptions::FormatterOperandOptions(Iced::Intel::MemorySizeOptions options)
	{
		flags = static_cast<std::uint32_t>(options) << static_cast<std::int32_t>(Flags::MemorySizeShift);
	}

	Iced::Intel::NumberBase NumberFormattingOptions::GetNumberBase() const
	{
		return static_cast<Iced::Intel::NumberBase>(numberBaseByteValue);
	}

	void NumberFormattingOptions::SetNumberBase(Iced::Intel::NumberBase value)
	{
		numberBaseByteValue = static_cast<std::uint8_t>(value);
	}

	NumberFormattingOptions NumberFormattingOptions::CreateImmediate(FormatterOptions* options)
	{
		if (options == nullptr)
		{
			ThrowHelper::ThrowArgumentNullException_options();
		}
		return CreateImmediateInternal(options);
	}

	NumberFormattingOptions NumberFormattingOptions::CreateImmediateInternal(FormatterOptions* options)
	{
		return NumberFormattingOptions(options, options->GetLeadingZeros(), options->GetSignedImmediateOperands(), false);
	}

	NumberFormattingOptions NumberFormattingOptions::CreateDisplacement(FormatterOptions* options)
	{
		if (options == nullptr)
		{
			ThrowHelper::ThrowArgumentNullException_options();
		}
		return CreateDisplacementInternal(options);
	}

	NumberFormattingOptions NumberFormattingOptions::CreateDisplacementInternal(FormatterOptions* options)
	{
		return NumberFormattingOptions(options, options->GetLeadingZeros(), options->GetSignedMemoryDisplacements(), options->GetDisplacementLeadingZeros());
	}

	NumberFormattingOptions NumberFormattingOptions::CreateBranch(FormatterOptions* options)
	{
		if (options == nullptr)
		{
			ThrowHelper::ThrowArgumentNullException_options();
		}
		return CreateBranchInternal(options);
	}

	NumberFormattingOptions NumberFormattingOptions::CreateBranchInternal(FormatterOptions* options)
	{
		return NumberFormattingOptions(options, options->GetBranchLeadingZeros(), false, false);
	}

	NumberFormattingOptions::NumberFormattingOptions(FormatterOptions* options, bool leadingZeros, bool signedNumber, bool displacementLeadingZeros)
	{
		if (options == nullptr)
		{
			ThrowHelper::ThrowArgumentNullException_options();
		}
		LeadingZeros = leadingZeros;
		SignedNumber = signedNumber;
		DisplacementLeadingZeros = displacementLeadingZeros;
		numberBaseByteValue = static_cast<std::uint8_t>(options->GetNumberBase());
		DigitSeparator = options->GetDigitSeparator();
		UppercaseHex = options->GetUppercaseHex();
		SmallHexNumbersInDecimal = options->GetSmallHexNumbersInDecimal();
		AddLeadingZeroToHexNumbers = options->GetAddLeadingZeroToHexNumbers();
		std::int32_t digitGroupSize;
		switch (options->GetNumberBase())
		{
		case NumberBase::Hexadecimal:
			Prefix = options->GetHexPrefix();
			Suffix = options->GetHexSuffix();
			digitGroupSize = options->GetHexDigitGroupSize();
			break;
		case NumberBase::Decimal:
			Prefix = options->GetDecimalPrefix();
			Suffix = options->GetDecimalSuffix();
			digitGroupSize = options->GetDecimalDigitGroupSize();
			break;
		case NumberBase::Octal:
			Prefix = options->GetOctalPrefix();
			Suffix = options->GetOctalSuffix();
			digitGroupSize = options->GetOctalDigitGroupSize();
			break;
		case NumberBase::Binary:
			Prefix = options->GetBinaryPrefix();
			Suffix = options->GetBinarySuffix();
			digitGroupSize = options->GetBinaryDigitGroupSize();
			break;
		default:
			throw InvalidOperationException();
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
