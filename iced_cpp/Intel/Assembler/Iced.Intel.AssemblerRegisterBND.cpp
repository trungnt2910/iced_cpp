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

#include "Iced.Intel.AssemblerRegisterBND.h"
#include "../Iced.Intel.RegisterExtensions.h"

namespace Iced::Intel
{

	AssemblerRegisterBND::AssemblerRegisterBND(Register value)
	{
		if (!Iced::Intel::RegisterExtensions::IsBND(value))
		{
			throw ArgumentOutOfRangeException(std::format("Invalid register {0:s}. Must be a BND register", nameof(value)));
		}
		Value = value;
	}

	AssemblerRegisterBND::operator Register() const
	{
		return this->Value;
	}

	bool AssemblerRegisterBND::Equals(AssemblerRegisterBND other)
	{
		return Value == other.Value;
	}

	std::int32_t AssemblerRegisterBND::GetHashCode()
	{
		return static_cast<std::int32_t>(Value);
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override bool Equals(Object? obj)
	bool AssemblerRegisterBND::Equals(std::any obj)
	{
		AssemblerRegisterBND* other = std::any_cast<AssemblerRegisterBND>(&obj);
		return other != nullptr && Equals(*other);
	}

	bool AssemblerRegisterBND::operator == (AssemblerRegisterBND right)
	{
		return this->Equals(right);
	}

	bool AssemblerRegisterBND::operator != (AssemblerRegisterBND right)
	{
		return !this->Equals(right);
	}
}
