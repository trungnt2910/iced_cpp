// C# helper headers

#include <csharp/enum.h>



// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "FastFormatterOptions.h"

namespace Iced::Intel
{

	FastFormatterOptions::FastFormatterOptions()
	{
		flags1 = Flags1::UsePseudoOps | Flags1::UppercaseHex;
	}

	bool FastFormatterOptions::GetSpaceAfterOperandSeparator() const
	{
		return (flags1 & Flags1::SpaceAfterOperandSeparator) != 0;
	}

	void FastFormatterOptions::SetSpaceAfterOperandSeparator(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::SpaceAfterOperandSeparator;
		}
		else
		{
			flags1 &= ~Flags1::SpaceAfterOperandSeparator;
		}
	}

	bool FastFormatterOptions::GetRipRelativeAddresses() const
	{
		return (flags1 & Flags1::RipRelativeAddresses) != 0;
	}

	void FastFormatterOptions::SetRipRelativeAddresses(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::RipRelativeAddresses;
		}
		else
		{
			flags1 &= ~Flags1::RipRelativeAddresses;
		}
	}

	bool FastFormatterOptions::GetUsePseudoOps() const
	{
		return (flags1 & Flags1::UsePseudoOps) != 0;
	}

	void FastFormatterOptions::SetUsePseudoOps(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::UsePseudoOps;
		}
		else
		{
			flags1 &= ~Flags1::UsePseudoOps;
		}
	}

	bool FastFormatterOptions::GetShowSymbolAddress() const
	{
		return (flags1 & Flags1::ShowSymbolAddress) != 0;
	}

	void FastFormatterOptions::SetShowSymbolAddress(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::ShowSymbolAddress;
		}
		else
		{
			flags1 &= ~Flags1::ShowSymbolAddress;
		}
	}

	bool FastFormatterOptions::GetAlwaysShowSegmentRegister() const
	{
		return (flags1 & Flags1::AlwaysShowSegmentRegister) != 0;
	}

	void FastFormatterOptions::SetAlwaysShowSegmentRegister(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::AlwaysShowSegmentRegister;
		}
		else
		{
			flags1 &= ~Flags1::AlwaysShowSegmentRegister;
		}
	}

	bool FastFormatterOptions::GetAlwaysShowMemorySize() const
	{
		return (flags1 & Flags1::AlwaysShowMemorySize) != 0;
	}

	void FastFormatterOptions::SetAlwaysShowMemorySize(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::AlwaysShowMemorySize;
		}
		else
		{
			flags1 &= ~Flags1::AlwaysShowMemorySize;
		}
	}

	bool FastFormatterOptions::GetUppercaseHex() const
	{
		return (flags1 & Flags1::UppercaseHex) != 0;
	}

	void FastFormatterOptions::SetUppercaseHex(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::UppercaseHex;
		}
		else
		{
			flags1 &= ~Flags1::UppercaseHex;
		}
	}

	bool FastFormatterOptions::GetUseHexPrefix() const
	{
		return (flags1 & Flags1::UseHexPrefix) != 0;
	}

	void FastFormatterOptions::SetUseHexPrefix(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::UseHexPrefix;
		}
		else
		{
			flags1 &= ~Flags1::UseHexPrefix;
		}
	}
}
