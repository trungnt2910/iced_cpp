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

#include "Iced.Intel.AssemblerRegisterST.h"
#include "../RegisterExtensions.h"

namespace Iced::Intel
{

	AssemblerRegisterST::AssemblerRegisterST(Register value)
	{
		if (!Iced::Intel::RegisterExtensions::IsST(value))
		{
			throw ArgumentOutOfRangeException(std::format("Invalid register {0:s}. Must be a ST register", nameof(value)));
		}
		Value = value;
	}

	AssemblerRegisterST::operator Register() const
	{
		return this->Value;
	}

	bool AssemblerRegisterST::Equals(AssemblerRegisterST other)
	{
		return Value == other.Value;
	}

	std::int32_t AssemblerRegisterST::GetHashCode()
	{
		return static_cast<std::int32_t>(Value);
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override bool Equals(Object? obj)
	bool AssemblerRegisterST::Equals(std::any obj)
	{
		AssemblerRegisterST* other = std::any_cast<AssemblerRegisterST>(&obj);
		return other != nullptr && Equals(*other);
	}

	bool AssemblerRegisterST::operator == (AssemblerRegisterST right)
	{
		return this->Equals(right);
	}

	bool AssemblerRegisterST::operator != (AssemblerRegisterST right)
	{
		return !this->Equals(right);
	}
}
