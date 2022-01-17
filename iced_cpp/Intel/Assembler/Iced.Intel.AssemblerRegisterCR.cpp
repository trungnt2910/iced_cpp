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

#include "Iced.Intel.AssemblerRegisterCR.h"
#include "../Iced.Intel.RegisterExtensions.h"

namespace Iced::Intel
{

	AssemblerRegisterCR::AssemblerRegisterCR(Register value)
	{
		if (!Iced::Intel::RegisterExtensions::IsCR(value))
		{
			throw ArgumentOutOfRangeException(std::format("Invalid register {0:s}. Must be a CR register", nameof(value)));
		}
		Value = value;
	}

	AssemblerRegisterCR::operator Register() const
	{
		return this->Value;
	}

	bool AssemblerRegisterCR::Equals(AssemblerRegisterCR other)
	{
		return Value == other.Value;
	}

	std::int32_t AssemblerRegisterCR::GetHashCode()
	{
		return static_cast<std::int32_t>(Value);
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override bool Equals(Object? obj)
	bool AssemblerRegisterCR::Equals(std::any obj)
	{
		AssemblerRegisterCR* other = std::any_cast<AssemblerRegisterCR>(&obj);
		return other != nullptr && Equals(*other);
	}

	bool AssemblerRegisterCR::operator == (AssemblerRegisterCR right)
	{
		return this->Equals(right);
	}

	bool AssemblerRegisterCR::operator != (AssemblerRegisterCR right)
	{
		return !this->Equals(right);
	}
}
