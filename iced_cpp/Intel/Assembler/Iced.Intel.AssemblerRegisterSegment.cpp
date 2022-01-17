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

#include "Iced.Intel.AssemblerRegisterSegment.h"
#include "../Iced.Intel.RegisterExtensions.h"

namespace Iced::Intel
{

	AssemblerRegisterSegment::AssemblerRegisterSegment(Register value)
	{
		if (!Iced::Intel::RegisterExtensions::IsSegmentRegister(value))
		{
			throw ArgumentOutOfRangeException(std::format("Invalid register {0:s}. Must be a SegmentRegister register", nameof(value)));
		}
		Value = value;
	}

	AssemblerRegisterSegment::operator Register() const
	{
		return this->Value;
	}

	bool AssemblerRegisterSegment::Equals(AssemblerRegisterSegment other)
	{
		return Value == other.Value;
	}

	std::int32_t AssemblerRegisterSegment::GetHashCode()
	{
		return static_cast<std::int32_t>(Value);
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override bool Equals(Object? obj)
	bool AssemblerRegisterSegment::Equals(std::any obj)
	{
		AssemblerRegisterSegment* other = std::any_cast<AssemblerRegisterSegment>(&obj);
		return other != nullptr && Equals(*other);
	}

	bool AssemblerRegisterSegment::operator == (AssemblerRegisterSegment right)
	{
		return this->Equals(right);
	}

	bool AssemblerRegisterSegment::operator != (AssemblerRegisterSegment right)
	{
		return !this->Equals(right);
	}
}
